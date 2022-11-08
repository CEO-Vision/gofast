<script>
  jQuery('.form-file').on("change", function(){
    var filename = jQuery('.form-file').val().split('/').pop().split('\\').pop();
    jQuery(".uppy-status").html('<i class="fa fa-upload"></i> ' + filename);
  })
</script>
