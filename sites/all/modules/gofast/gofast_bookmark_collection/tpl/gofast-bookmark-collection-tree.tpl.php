<ul id="<?= $treeId ?>" class="ztree overflow-hidden text-nowrap"></ul>
<script>
  $(document).ready(()=>{
    Gofast.Bookmark_Collection.loadTree('<?= $treeId ?>')
  })
</script>