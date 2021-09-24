
(function ($) {
  "use strict";
  
  /**
   * Applies the soft limit to facets in the block realm.
   *  Support hierarchized facets as well.
   * 
   * @see facetapi/facetapi.js
   */
  Drupal.facetapi.applyLimit = function(settings) {
    if (settings.limit > 0 && !$('ul#' + settings.id).hasClass('facetapi-processed')) {
      // Only process this code once per page load.
      $('ul#' + settings.id).addClass('facetapi-processed');

      // Ensures our limit is zero-based, hides facets over the limit.
      var limit = settings.limit - 1;
      $('ul#' + settings.id).children('li:gt(' + limit + ')').hide();

      // Adds "Show more" / "Show fewer" links as appropriate.
      $('ul#' + settings.id).filter(function() {
        return $(this).children('li').length > settings.limit;
      }).each(function() {
        $('<a href="#" class="facetapi-limit-link"></a>').text(Drupal.t(settings.showMoreText, {}, {'context' : 'gofast'})).click(function() {
          if ($(this).siblings().children('li:hidden').length > 0) {
            $(this).siblings().children('li:gt(' + limit + ')').slideDown();
            $(this).addClass('open').text(Drupal.t(settings.showFewerText, {}, {'context' : 'gofast'}));
          }
          else {
            $(this).siblings().children('li:gt(' + limit + ')').slideUp();
            $(this).removeClass('open').text(Drupal.t(settings.showMoreText, {}, {'context' : 'gofast'}));
          }
          return false;
        }).insertAfter($(this));
      });
    }
  };
  
  // This strange little function allows the "expanded" class to be added to or
  // removed from the passed in facet based on the passed in condition, which
  // corresponds to a configured setting.
  var facetCollapseExpanded = function ($facet, condition, operation, behavior) {
    var wrapper = $facet.find('.facet-collapsible-wrapper').get(0);

    if (wrapper) {
      var facetId = wrapper.id.replace('facet-collapsible-', '').replace(/-/g, '_');

      if (Drupal.settings.gofast_search[facetId]) {
        // We either need to check that the 'condition' in Drupal.settings DOES
        // hold for the given facet's configuration, or that it DOES NOT hold. 
        // Only add or remove the class if the condition has been satisfied.
        if (Drupal.settings.gofast_search[facetId][condition] === operation) {
          // behavior is either "addClass" or "removeClass"
          $facet[behavior]('expanded');
        }
      }
    }
  };
  
  var facetSaveState = function (state) {
    $.cookie(
      'Facetapi.collapsible.expanded',
      JSON.stringify(state), {
        path: Drupal.settings.basePath,
        expires: 1
      }
    );
  }

  /**
   * Behavior for collapsing faceted search lists.
   */
  Drupal.behaviors.facetapiCollapsible = {
    attach : function (context) {
      // Check cookie
      var state = $.parseJSON($.cookie('Facetapi.collapsible.expanded')) || {};
      
      $('.facetapi-collapsible').once('facetapi-collapsible', function () {
        var $facet = $(this);

        if ($('.facetapi-active', this).size() > 0) {
          $(this).addClass('expanded active');
        }
        else {
          // Add the 'expanded' class to the facet if configured to do so.
          facetCollapseExpanded($facet, 'expand', 1, 'addClass');
          
          var wrapper = $('.facet-collapsible-wrapper', $facet).get(0),
              facetId;
          
          if (wrapper) {
            facetId = wrapper.id.replace('facet-collapsible-', '').replace(/-/g, '_');
            state[facetId] = state[facetId] || [];
            if (state[facetId].indexOf('expanded') !== -1) {
              $facet.addClass('expanded');
            }
          }

          // Expand/Collapse facet block on click.
          $('h2', $facet).click(function () {
            $facet.siblings('.facetapi-collapsible:not(.active)').each(function () {
              // Remove the 'expanded' class from all other facets that haven't
              // been configured to stay open.
              facetCollapseExpanded($(this), 'keep_open', 0, 'removeClass');
            });

            wrapper && $(wrapper).slideToggle(300, 'swing', function() {
              $facet.toggleClass('expanded');
              if (wrapper && facetId) {
                var blockState = $facet.hasClass('expanded') ? 'expanded' : 'collapsed';
                state[facetId] = Gofast.apply(state[facetId] || [], [blockState]);
                facetSaveState(state);
              }              
            });
          });
        }
        
        $('.facetapi-collapsible ul.facetapi-collapsible ul').once('facetlist', function () {
          var $list = $(this),
              parentwrapper = $list.closest('.facet-collapsible-wrapper');

          if (parentwrapper) {
            var parentfacetId = parentwrapper.attr('id').replace('facet-collapsible-', '').replace(/-/g, '_');
            
            if (Drupal.settings.gofast_search[parentfacetId] && Drupal.settings.gofast_search[parentfacetId].collapsible_children) {
              var $parentfacet = $($list.siblings('.facetapi-facet').get(0));

              // Init facet items state (default is collapsed).
              $('a', $parentfacet).each(function () {
                var $facetItem = $(this),
                    $facetHandle = $('<span class="facetapi-collapsible-handle"></span>'),
                    $facetTree = $facetItem.closest('.facetapi-facet').siblings('ul').first().add($facetItem.closest('li'));
                
                // Insert handle before the facet.
                $facetItem.prepend($facetHandle);
                
                if (state[parentfacetId] && (state[parentfacetId].indexOf($facetItem.attr('href')) > 0)) {
                  $facetHandle.add($facetTree).toggleClass('expanded'); //
                }
              }).addClass('collapselink');

              // Expand facet with active childs.
              if ($('a.facetapi-active', $list).length) {
                $('ul', $list.closest('div')).first().addClass('expanded');
              }

              // Collapse/Expand on click
              $('a .facetapi-collapsible-handle', $parentfacet).click(function (event) {
                var $clickedlist = $parentfacet.siblings('ul'),
                    $clickedlink = $(this).closest('a'),
                    $handle = $(this);
                
                $clickedlist.slideToggle(300, 'swing', function() {
                  state[parentfacetId] = state[parentfacetId] || [];
                  $clickedlist.add($clickedlist.closest('li')).toggleClass('expanded'); //

                  $handle.toggleClass('expanded');
                  if ($clickedlist.hasClass('expanded')) {
                    state[parentfacetId].push($clickedlink.attr('href'));
                  }
                  else {
                    var index = state[parentfacetId].indexOf($clickedlink.attr('href'));
                    if (index !== -1) {
                      state[parentfacetId].splice(index, 1);
                    }                  
                  }

                  if (Drupal.settings.gofast_search[parentfacetId].keep_open === false) {
                    $('ul', $list.closest('li').siblings('li')).each(function () {
                      $(this).removeClass('expanded');
                      $('a .facetapi-collapsible-handle', $(this).closest('li')).html('+');

                      var index = state[parentfacetId].indexOf($('a', $(this).closest('li')).attr('href'));
                      if (index !== -1) {
                        state[parentfacetId].splice(index, 1);
                      }
                    });
                  }
                });
                
                facetSaveState(state);
                event.preventDefault();
              });
            }
          }
        });
        
        $('.facetapi-collapsible ul.facetapi-collapsible li.leaf').once('facetleaf', function () {
          // Insert handle before the facet.
          $('a', $(this)).prepend('<span class="facetapi-handle-leaf"></span>');              
        });
        
      });
    }
  };
})(jQuery);