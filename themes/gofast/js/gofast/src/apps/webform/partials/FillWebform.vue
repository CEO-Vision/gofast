<template>
  <div class="h-100">
    <AlertContent
      v-if="props.webformStatus == 'closed'"
      :message="props.webformStatusMessage"
    />
    <SurveyComponent
      v-if="props.webformStatus != 'closed' && survey"
      :model="survey"
    />
  </div>
</template>

<script setup>
import { ref, onMounted } from 'vue';
import axios from 'axios';
import { Model, surveyLocalization } from 'survey-core';
import { SurveyPDF } from 'survey-pdf';
import { defaultTheme } from '../survey_default_theme';
import 'survey-core/defaultV2.min.css';
import AlertContent from '../../../components/global/AlertContent.vue';
import { getCurrentUser, getCurrentLanguage } from '../../gofast/utils/utils';
import 'survey-core/survey.i18n';

const props = defineProps({
  nid: {
    type: String,
    required: true,
  },
  webform: {
    type: Object,
    required: true,
  },
  webformTheme: {
    type: Object,
    required: false,
    default: defaultTheme,
  },
  webformStatus: {
    type: String,
    required: true,
  },
  webformStatusMessage: {
    type: String,
    required: false,
    default: '',
  },
});

const isLoading = ref(true);
const surveyJson = ref({});
const survey = ref();
const tempFileStorage = {};
const dataPdfUpload = ref({});
const submissionFolderReference = ref('');
const pdfDocOptions = {
  matrixRenderAs: 'list',
  compress: true,
};

const lang = getCurrentLanguage();
surveyLocalization.defaultLocale = lang;

let user = getCurrentUser();
if (user === undefined) {
  user = 0;
}

function saveData() {
  const formDataSubmit = new FormData();
  const formDataPdfUpload = dataPdfUpload.value;

  formDataSubmit.append('data', JSON.stringify(survey.value.data));
  formDataSubmit.append('correctAnswer', survey.value.getCorrectAnswerCount());
  formDataSubmit.append('timeSpent', survey.value.timeSpent);
  formDataSubmit.append(
    'getQuizQuestionCount',
    survey.value.getQuizQuestionCount(),
  );
  formDataSubmit.append('pdfUpload', JSON.stringify(formDataPdfUpload));
  formDataSubmit.append(
    'submissionFolderReference',
    submissionFolderReference.value,
  );

  axios
    .post(`/api/webform/webform_submissions?nid=${props.nid}`, formDataSubmit, {
      headers: {
        'Content-Type': 'multipart/form-data',
      },
    })
    .then((response) => {
      console.log(response);
      // Handle success
    })
    .catch((_error) => {
      // Handle error
    });
}

async function uploadFiles() {
  const surveyPdf = new SurveyPDF(surveyJson.value, pdfDocOptions);
  surveyPdf.mode = 'display';
  surveyPdf.data = survey.value.data;
  await surveyPdf.raw('blob').then(async (blob) => {
    const formFileUpload = new FormData();
    const questionsToUpload = Object.keys(tempFileStorage);

    questionsToUpload.forEach((questionName) => {
      const filesToUpload = tempFileStorage[questionName];
      filesToUpload.forEach((file) => {
        formFileUpload.append(questionName, file);
      });
    });

    formFileUpload.append('surveySubmissionPdf', blob, 'surveySubmission.pdf');
    formFileUpload.append('nid', props.nid);

    try {
      const response = await fetch(`/api/webform/file`, {
        method: 'POST',
        body: formFileUpload,
      });
      const data = await response.json();

      submissionFolderReference.value = data.submission_folder_reference;
      dataPdfUpload.value = data.surveySubmissionPdf;
      questionsToUpload.forEach((questionName) => {
        const filesToUpload = tempFileStorage[questionName];
        const question = survey.value.getQuestionByName(questionName);
        question.value = filesToUpload.map(() => {
          return {
            name: `${data[questionName].file_name}`,
            reference: `${data[questionName].file_reference}`,
          };
        });
      });
    } catch (error) {
      // Handle error
    }
  });
}

function savePdf(surveyData) {
  const surveyPdf = new SurveyPDF(surveyJson.value, pdfDocOptions);
  surveyPdf.mode = 'display';
  surveyPdf.data = surveyData;
  surveyPdf.save();
}

async function loadSurvey() {
  isLoading.value = true;
  surveyJson.value = props.webform;
  if (!survey.value) {
    survey.value = new Model(surveyJson.value);
    if (props.webformTheme) {
      survey.value.applyTheme(props.webformTheme);
    } else {
      survey.value.applyTheme(defaultTheme);
    }
    survey.value.onComplete.add(async () => {
      await uploadFiles();
      saveData(props.nid, survey);
    });
    survey.value.addNavigationItem({
      id: 'pdf-export',
      title: Drupal.t('Save as PDF', {}, { context: 'gofast:gofast_webform' }),
      action: () => savePdf(survey.value.data),
    });
    // Handles selected files
    survey.value.onUploadFiles.add((_, options) => {
      // Add files to the temporary storage
      if (tempFileStorage[options.name] !== undefined) {
        tempFileStorage[options.name] = tempFileStorage[options.name].concat(
          options.files,
        );
      } else {
        tempFileStorage[options.name] = options.files;
      }
      // Load file previews
      const content = [];
      options.files.forEach((file) => {
        const fileReader = new FileReader();
        fileReader.onload = () => {
          content.push({
            name: file.name,
            type: file.type,
            content: fileReader.result,
            file,
          });
          if (content.length === options.files.length) {
            // Return a file for preview as a { file, content } object
            options.callback(
              content.map((fileContent) => {
                return {
                  file: fileContent.file,
                  content: fileContent.content,
                };
              }),
            );
          }
        };
        fileReader.readAsDataURL(file);
      });
    });

    // Handles file removal
    survey.value.onClearFiles.add((_, options) => {
      // Empty the temporary file storage if "Clear All" is clicked
      if (options.fileName === null) {
        tempFileStorage[options.name] = [];
        options.callback('success');
        return;
      }

      // Remove an individual file
      const tempFiles = tempFileStorage[options.name];
      if (tempFiles) {
        const fileInfoToRemove = tempFiles.filter(
          (file) => file.name === options.fileName,
        )[0];
        if (fileInfoToRemove) {
          const index = tempFiles.indexOf(fileInfoToRemove);
          tempFiles.splice(index, 1);
        }
      }
      options.callback('success');
    });
  } else {
    survey.value.fromJSON(surveyJson.value);
  }
  isLoading.value = false;
}

onMounted(() => {
  loadSurvey();
});
</script>
