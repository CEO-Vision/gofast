window.initFileInput = (
  restrictions = {
    maxFileSize: 35000000,
    maxNumberOfFiles: 1,
    allowedFileTypes: ["image/*", "text/*", "application/*"],
  },
  thumbnail = false
) => {
  // we want to keep our Drupal input in order for the backend to handle the file
  // there may be several file inputs in the same page so if that's the case we have to handle them all
  const drupalFileInputs = document.querySelectorAll(
    ".uppy-Root > span > input[type='file']"
  )
  for (const drupalFileInput of drupalFileInputs) {
    // If the input has attributes overriding the allowed file types
    if ($(drupalFileInput).attr("data-allowed")) {
      restrictions.allowedFileTypes = $(drupalFileInput).attr("data-allowed").split(";");
    }
    const uppy = new Uppy.Core({
      autoProceed: true,
      allowMultipleUploads: false,
      restrictions: restrictions
    })
      .use(Uppy.StatusBar, {
        target: ".uppy-status",
        hideUploadButton: true,
        hideAfterFinish: false,
      })
      .use(Uppy.Informer, { target: ".uppy-informer" });
    const uppyRoot = drupalFileInput.closest(".uppy").parentElement;
    drupalFileInput.addEventListener("change", (event) => {
      const uppyRoot = event.currentTarget.closest(".uppy").parentElement;
      uppyRoot.querySelector(".uppy.form-type-file").insertAdjacentHTML("beforeend", "<div class='spinner uppy-spinner'></div>");
      const files = Array.from(event.target.files);
      files.forEach((file) => {
        try {
          const fileId = uppy.addFile({
            source: "file input",
            name: file.name,
            type: file.type,
            data: file,
          });
          uppy.setFileState(fileId, {
            progress: { uploadComplete: true, uploadStarted: false },
          });
        } catch (err) {
          uppyRoot.querySelector(".uppy-spinner").remove();
          if (err.isRestriction) {
            // handle restrictions
            console.log("Restriction error:", err);
          } else {
            // handle other errors
            console.error(err);
          }
        }
      });
    });
    uppy.on("complete", (result) => {
      // original preview displayed before the first upload: remove it as soon as a newly uploaded content has to be previewed
      if ($(drupalFileInput).attr("data-preview")) {
        const previewTarget = "#" + $(drupalFileInput).attr("data-preview");
        $(previewTarget).remove();
      }
      uppyRoot.querySelector(".uppy-spinner").remove();
      if (thumbnail) {
        const imgContainer = drupalFileInput.closest(".uppy.form-type-file").querySelector(".text-muted");
        // relies on the MIME type to know if the thumbnail must be displayed in an iframe or an img tag
        const isPdf = result.successful[0].id.includes("application/pdf");
        const img = isPdf ? document.createElement('iframe') : document.createElement('img');
        if (isPdf) {
          img.style.width = "100%";
          img.style.height = "100%";
        } else {
          img.width = 100;
        }
        img.src = URL.createObjectURL(drupalFileInput.files[0]);
        imgContainer.innerHTML = "";
        imgContainer.insertAdjacentElement("beforeend", img);      
      }
      Gofast.toast(
        result.successful[0].name + " " + Drupal.t(" has been detected succesfully"),
        "info"
      );
      uppy.reset();
    });
  }
};

class GofastCKEditorUploadAdapter {
  constructor(loader, url) {
    this.loader = loader;
    this.url = url;
  }

  _initRequest() {
    const xhr = this.xhr = new XMLHttpRequest();
    xhr.open('POST', this.url, true);
    xhr.responseType = 'json';
  }

  // Starts the upload process.
  upload() {
    return this.loader.file
      .then( file => new Promise((resolve, reject) => {
        this._initRequest();
        this._initListeners(resolve, reject, file);
        this._sendRequest(file);
      }));
  }

  // Aborts the upload process.
  abort() {
    if (this.xhr) {
      this.xhr.abort();
    }
  }

  // Initializes XMLHttpRequest listeners.
  _initListeners(resolve, reject, file) {
    const xhr = this.xhr;
    const loader = this.loader;
    const genericErrorText = "Couldn't upload file: " + file.name;

    xhr.addEventListener('error', () => reject(genericErrorText));
    xhr.addEventListener('abort', () => reject() );
    xhr.addEventListener('load', () => {
      const response = xhr.response;

      if (!response || response.error) {
        return reject(response && response.error ? response.error.message : genericErrorText);
      }

      resolve({
        default: response.url
      });
    });

    if (xhr.upload) {
      xhr.upload.addEventListener('progress', evt => {
        if (evt.lengthComputable) {
          loader.uploadTotal = evt.total;
          loader.uploaded = evt.loaded;
        }
      });
    }
  }

  // Prepares the data and sends the request.
  _sendRequest(file) {
      // Prepare the form data.
      const data = new FormData();
      data.append('upload', file );

      // Send the request.
      this.xhr.send(data);
  }
}

window.GofastCKEditorUploadAdapterPlugin = function(ckeditor) {
  ckeditor.plugins.get('FileRepository').createUploadAdapter = (loader) => {
      const url = "/sites/all/libraries/ckeditor/CKEditorUploader/upload.php";
      return new GofastCKEditorUploadAdapter(loader, url);
  };
}