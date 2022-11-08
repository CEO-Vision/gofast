window.initFileInput = (
  restrictions = {
    maxFileSize: 35000000,
    maxNumberOfFiles: 1,
    allowedFileTypes: ["image/*", "text/*", "application/*"],
  },
  thumbnail = false
) => {
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

  // we want to keep our Drupal input in order for the backend to handle the file
  const drupalFileInput = document.querySelector(
    ".uppy-Root > span > input[type='file']"
  );
  drupalFileInput.addEventListener("change", (event) => {
    document.querySelector(".uppy.form-type-file").insertAdjacentHTML("beforeend", "<div class='spinner uppy-spinner'></div>");
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
        document.querySelector(".uppy-spinner").remove();
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
    document.querySelector(".uppy-spinner").remove();
    if (thumbnail) {
      const imgContainer = document.querySelector(".uppy.form-type-file > .text-muted");
      const img = document.createElement('img');
      img.src = URL.createObjectURL(drupalFileInput.files[0]);
      img.width = 100;
      imgContainer.innerHTML = "";
      imgContainer.insertAdjacentElement("beforeend", img);      
    }
    Gofast.toast(
      result.successful[0].name + " " + Drupal.t(" has been detected succesfully"),
      "info"
    );
    uppy.reset();
  });
};
