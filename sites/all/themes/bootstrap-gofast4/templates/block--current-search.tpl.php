<?php
/**
 * @file
 * Default theme implementation to display a block.
 *
 * Available variables:
 * - $block->subject: Block title.
 * - $content: Block content.
 * - $block->module: Module that generated the block.
 * - $block->delta: An ID for the block, unique within each module.
 * - $block->region: The block region embedding the current block.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - block: The current template type, i.e., "theming hook".
 *   - block-[module]: The module generating the block. For example, the user
 *     module is responsible for handling the default user navigation block. In
 *     that case the class would be 'block-user'.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $block_zebra: Outputs 'odd' and 'even' dependent on each block region.
 * - $zebra: Same output as $block_zebra but independent of any block region.
 * - $block_id: Counter dependent on each block region.
 * - $id: Same output as $block_id but independent of any block region.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $block_html_id: A valid HTML ID and guaranteed unique.
 *
 * @see bootstrap_preprocess_block()
 * @see template_preprocess()
 * @see template_preprocess_block()
 * @see bootstrap_process_block()
 * @see template_process()
 *
 * @ingroup templates
 */
//print_r($title); exit;
?>
<section id="<?php print $block_html_id; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?> style="border:none;padding:0px;">
    <div id='search_tab'>
     <ul class="nav nav-tabs nav-justified" role="tablist">
          <li role="presentation" class="active"><a id="searchtab_current" href="#search_current" aria-controls="search_current" role="tab" data-toggle="tab"><?php print t("Current search", array(), array("context" => "gofast")); ?></a></li>
          <li role="presentation" ><a id="searchtab_saved" href="#search_saved" aria-controls="search_saved" role="tab" data-toggle="tab"><?php print t("My saved searches", array(), array("context" => "gofast:search")); ?></a></li>
     </ul>
     <div class="tab-content content well well-sm" style="margin-bottom:2px;">
          <div role="tabpanel" class="tab-pane active" id="search_current">
            <div class="container container-number-results" style="float:left;width:80%;">             
                <?php print $content ?>
            </div>
            <div style="float:right;">
                 <a style="padding:4px;color:#2980b9; " type="button" class="btn btn-default ctools-use-modal fa fa-lg fa-save" title='<?php print t("Save this search", array(), array("context" => "gofast:search")); ?>' href="/modal/nojs/search/save"></a>
            </div>
              <div style="clear:both;"></div>
          </div>
          <div role="tabpanel" class="tab-pane" id="search_saved"  >           
            <?php
                 $block = module_invoke('gofast_search', 'block_view', 'gofast_saved_searches');
                 print $block['content'];
            ?>
          </div>
     </div>
    </div>
</section>

<section  class="block block-facetapi contextual-links-region facetapi-collapsible clearfix container-filter expanded" style="">
    <h2 class="block-title"><i class="fa pull-left fa-chevron-down"></i><?php echo t("Search options", array(), array("context" => "gofast"));?></h2>  
        <?php $options = gofast_search_options(); ?> 
        <div class="facet-collapsible-wrapper" style="" id="facetapi_search_filters">
            <ul class="facetapi-gofast-facetapi-links facetapi-collapsible">
                    <!-- Strict search -->
                    <?php $strict_default_value = $_COOKIE["strict_search"];
                            if($strict_default_value == "true" || !isset($_COOKIE["strict_search"])){ 
                                $strict_default_value = "checked";
                            }else{
                                $strict_default_value = "";             
                            }
                    ?>
                <div style="margin:5px;">
                    <input data-size="mini" id="edit-strict_search-update" class="form-checkbox" value=" " type="checkbox" <?php echo $strict_default_value; ?> >
                    <?php $help_strict_search = t("A strict search means all keywords are mandatories ( except if they start by - ) and they must be exactly the same as on the document", array(), array("context" => "gofast:search")); ?>
                    <span style='' href="#" title="<?php echo t("Strict search", array(), array("context" => "gofast:search")); ?>" ><?php echo t("Strict search", array(), array("context" => "gofast:search")); ?></span> <i title="<?php echo $help_strict_search; ?>" class="fa fa-question-circle" style=" color: #777;cursor:pointer;"></i>
                </div>
                   <!-- end strict search -->
                <?php foreach ($options as $name => $option) { ?>
                <div style="margin:5px;">
                <input data-size="mini" type="checkbox" item="<?php echo $name ?>" name="<?php echo $name ?>" <?php if(($option['value']== '1')){ echo 'checked=true'; } ?>>
                <span style='' href="#" title="<?php echo $option['title'] ?>" ><?php echo $option['title'] ?></span>
                </div>
                <?php } ?>
            </ul>
        </div>
</section >
    