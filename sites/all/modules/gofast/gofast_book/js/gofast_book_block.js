
(function ($, Gofast, Drupal) {         
  const explorerWikiInterval = setInterval(function() {
    if (!$('#explorer-wiki').length) {
        return;
    }
          $("#explorer-wiki").on('click', function(){      
            if($("#wiki .gofast-spinner-xxl").length == 1){
              setTimeout(function(){
          $.get(window.origin + "/gofast/book/explorer").done(function(data){
            $("#wiki").html(data);
            Gofast.selectCurrentWikiArticle();
          });
        }, 500); 
      }
    })
    clearInterval(explorerWikiInterval);
  },100)

  Gofast.book = Gofast.book || {};

  Gofast.book.refreshBrowser = function() {
    // find container
    let container = $(this).closest(".book-explorer-widget");
    if (!container.length) {
      container = $(this).closest(".book-explorer-main");
    }
    // parse params
    let widget = false;
    let bookExplorerParams = [];
    if ($(this).attr("data-widget") != undefined) {
      widget = true;
      bookExplorerParams.push("widget");
    }
    if ($(this).attr("data-has-links") != undefined) {
      bookExplorerParams.push("has_links");
    }
    // build query string
    let bookExplorerQueryString = "";
    if(bookExplorerParams.length) {
      bookExplorerQueryString = "?";
      for (const param of bookExplorerParams) {
        bookExplorerQueryString.concat(param + "=true");
      }
    }
    // get stuff
    container.html('<div class="d-flex min-h-200px min-w-40px h-100 w-100"><div class="spinner spinner-primary m-auto"></div></div>');
    $.get(window.origin + "/gofast/book/explorer" + bookExplorerQueryString).done(function(data){
      container.replaceWith(data);
    });
    if (!widget) {
      Gofast.selectCurrentWikiArticle();

    }
  }

  Gofast.book.searchBrowser = function() {
    clearTimeout(Gofast.ITHitMobile.searchProcess);
    const value =$(this).val();
    const elements = $(this).closest(".book-explorer-wrapper").find(".book-explorer-element");

    Gofast.ITHitMobile.searchProcess = setTimeout(function(){
      Gofast.ITHitMobile.search(
        value,
        false,
        true,
        elements
      );
    });
  }

  Gofast.book.treeWidgetItemCollapseCallback = function() {
    const $bookOpenElement = $(this);

    // toggle chevron of clicked element and keep track whether we're collapsing or not to handle children elements
    let collapse = true;
    if ($bookOpenElement.hasClass("ki-bold-arrow-next")) {
        collapse = false;
        $bookOpenElement.removeClass("ki-bold-arrow-next").addClass("ki-bold-arrow-down");
    } else {
        $bookOpenElement.removeClass("ki-bold-arrow-down").addClass("ki-bold-arrow-next");
    }

    const $bookItemElement = $bookOpenElement.parent().parent();
    if (collapse) {
        Gofast.book.closeItemSiblings($bookItemElement);
    } else {
        Gofast.book.openItemSiblings($bookItemElement, "DESC", false);
    }
  }

  Gofast.book.closeItemSiblings = function(selector, direction = "DESC", recursive = true, initialCall = true) {
    const $widgetSiblings = $(selector);

    // we don't want to hide the first item since it's the parent of the closed items
    if (!initialCall && direction == "DESC") {
      $widgetSiblings.removeClass("book-explorer-element-visible").addClass("book-explorer-element-collapsed");
    }
    $widgetSiblings.find(".book-explorer-element-open").removeClass("ki-bold-arrow-down").addClass("ki-bold-arrow-next");
  
    if (!recursive && !initialCall) {
      return;
    }

    const widgetTableId = $widgetSiblings.closest(".book_element-explorer-element-table").attr("id")
    let nextWidgetSiblingSelector = [];

    if (direction == "DESC") {
      for (const widgetSibling of $widgetSiblings) {
        const currentWidgetSiblingId = $(widgetSibling).attr("id");
        if (currentWidgetSiblingId != undefined && currentWidgetSiblingId != 0) {
          nextWidgetSiblingSelector.push("#" + widgetTableId + " [data-pid='" + currentWidgetSiblingId + "']");
        }
      }
    } else {
      for (const widgetSibling of $widgetSiblings) {
        const nextWidgetSiblingId = $(widgetSibling).find(".book-explorer-element-parent").text().trim();
        if (nextWidgetSiblingId != undefined && nextWidgetSiblingId != 0) {
          nextWidgetSiblingSelector.push("#" + widgetTableId + " #"  + nextWidgetSiblingId);
        }
      }
    }
    nextWidgetSiblingSelector = nextWidgetSiblingSelector.join(", ");
    const $nextSiblings = $(nextWidgetSiblingSelector);
    if ($nextSiblings.length) {
      Gofast.book.closeItemSiblings($nextSiblings, direction, recursive, false);
    } else if (direction == "ASC") {
      // we don't want to hide a root item
      $widgetSiblings.removeClass("book-explorer-element-collapsed").addClass("book-explorer-element-visible");
    }
  }

  Gofast.book.openItemSiblings = function(selector, direction = "ASC", recursive = true, initialCall = true) {
    const $widgetSiblings = $(selector);
    const widgetTableId = $widgetSiblings.closest(".book_element-explorer-element-table").attr("id");

    // if in ascending order, still open the first level descendants of the start items
    if (initialCall && direction == "ASC") {
      for (const widgetSibling of $widgetSiblings) {
        const currentWidgetSiblingId = $(widgetSibling).attr("id");
        $("#" + widgetTableId + " [data-pid='" + currentWidgetSiblingId + "']").removeClass("book-explorer-element-collapsed").addClass("book-explorer-element-visible");
        $(widgetSibling).find(".book-explorer-element-open").removeClass("ki-bold-arrow-next").addClass("ki-bold-arrow-down");
      }
    }
    // make sure we actually display all the siblings of the passed siblings
    for (const widgetSibling of $widgetSiblings) {
      const currentWidgetSiblingPid = $(widgetSibling).attr("data-pid");
      $("#" + widgetTableId + " [data-pid='" + currentWidgetSiblingPid + "']").removeClass("book-explorer-element-collapsed").addClass("book-explorer-element-visible");
      $("#" + widgetTableId + " #"+ currentWidgetSiblingPid).find(".book-explorer-element-open").removeClass("ki-bold-arrow-next").addClass("ki-bold-arrow-down");
    }

    if (!recursive && !initialCall) {
      return;
    }

    let nextWidgetSiblingSelector = [];

    if (direction == "ASC") {
      for (const widgetSibling of $widgetSiblings) {
        const nextWidgetSiblingId = $(widgetSibling).find(".book-explorer-element-parent").text().trim();
        if (nextWidgetSiblingId != undefined && nextWidgetSiblingId != 0) {
          nextWidgetSiblingSelector.push("#" + widgetTableId + " #" + nextWidgetSiblingId);
        }
      }
    } else {
      for (const widgetSibling of $widgetSiblings) {
        const currentWidgetSiblingId = $(widgetSibling).attr("id");
        if (currentWidgetSiblingId != undefined && currentWidgetSiblingId != 0) {
          nextWidgetSiblingSelector.push("#" + widgetTableId + " [data-pid='" + currentWidgetSiblingId + "']");
        }
      }
    }
    nextWidgetSiblingSelector = nextWidgetSiblingSelector.join(", ");
    const $nextSiblings = $(nextWidgetSiblingSelector);
    if ($nextSiblings.length) {
      Gofast.book.openItemSiblings($nextSiblings, direction, recursive, false);
    }
  }

  Gofast.book.updatePageSelector = function($widgetForm, gid) {
    $pageSelector = $widgetForm.find("select#edit-page-selector");
    let nid = 0;
    $.get("/space/book/" + gid).done(function(data) {
        if (!data) {
          return;
        }
        $pageSelector.html("");
        // Use this for create the under-wiki (data == 0 && !isParent)
        // const isParent = $('.wiki-tree-widget-item.book-explorer-element.book-explorer-element-visible.active').attr("data-pid") === "0";
        // data.length == 0 && !isParent
        if (data == 1 ) {
          const selectedNid = $widgetForm.find("#book_explorer_body").attr("data-selected");
          const selectedTitle = $widgetForm.find(".wiki-tree-widget-item[data-nid='" + selectedNid + "'").attr("data-name");
          $pageSelector.append(
            '"<option value="0">' + "W00 - " + Drupal.t("Create new subwiki for", {}, {context: "gofast:gofast_book"}) + ' <span class="font-weight-bold">"' + selectedTitle + '"</span></option>'
          );
          return;
        }
       
        const nameWiki = $('.wiki-tree-widget-item.book-explorer-element.book-explorer-element-visible.active .wiki-tree-widget-item-name.item-name.wiki-processed').text();
        $pageSelector.append("<option value='"+gid+"'>" + "W000 - " + Drupal.t("Insert at the start of the wiki", {}, {context: "gofast:gofast_book"})+ '<span class="font-weight-bold">"' + nameWiki.trim() + '"</span></option>');
        
        $("#gofast_book_weights").val(JSON.stringify(data));
        let pageCounter = 0;
        for (const wikiItem of data) {
            if(wikiItem.nid == nid) {
                $previousElement = $pageSelector.find("option").last();
                $previousElement.attr("selected", "");
                continue;
            }
            pageCounter++;
            const paddedPageCounter = String(pageCounter).padStart(3, "0");
            $pageSelector.append(
              '<option value="' + wikiItem.nid + '">' + "W" + paddedPageCounter + " - " + Drupal.t("Insert after the page", {}, {context: "gofast:gofast_book"}) + ' <span class="font-weight-bold">"' + wikiItem.name + '"</span></option>'
          );
          
        }
        $pageSelector.on("change", function() {
          const selectedNid = $(this).val();
          const $selectedItem = $widgetForm.find(".wiki-tree-widget-item[data-nid='" + selectedNid + "']");
          
          // Remove 'active' and 'selected-option' classes from all elements in the tree
          $widgetForm.find(".wiki-tree-widget-item.active").removeClass("active");
          $widgetForm.find(".wiki-tree-widget-item td.book-explorer-element-icon.selected-option").removeClass("selected-option");
          
          if (selectedNid) {
            // Add 'active' and 'selected-option' classes to the selected element in the tree
            $selectedItem.addClass("active");
            $selectedItem.find("td.book-explorer-element-icon").addClass("selected-option");
          
            // Open parents if the item is nested
            Gofast.book.openItemSiblings($selectedItem);
            $selectedItem[0].scrollIntoView({ behavior: "smooth", block: "center" });
          
            // Handle form inputs if the item is within a form
            const $selectedFormItem = $selectedItem.closest("form");
            if ($selectedFormItem.length) {
              Gofast.book.updatePageSelector($selectedFormItem, selectedNid);
              Gofast.book.updateLocationsInput($selectedFormItem, selectedNid);
            }
          }
        });
               
    });
  }

  Gofast.book.updateLocationsInput = function($widgetForm, gid) {
    $widgetForm.find("#wiki_tree_location_input").val(gid);
  }

  Gofast.book.treeWidgetItemCallback = function(e) {
    e.preventDefault();
    // get item with gid/nid attribute
    const $widgetItem = $(e.currentTarget).closest(".wiki-tree-widget-item");
    const nid = $widgetItem.attr("data-nid");

    const $bookExplorerBody = $widgetItem.closest("#book_explorer_body");
    const selectedNid = $bookExplorerBody.attr("data-selected");
  
    // Remove 'active' and 'selected-option' from previously selected elements
    $bookExplorerBody.find(".wiki-tree-widget-item.active").removeClass("active selected-option");
    $bookExplorerBody.find(".wiki-tree-widget-item td.book-explorer-element-icon.selected-option").removeClass("selected-option");
    if (selectedNid) {
      $widgetItem.closest("#book_explorer_body").find(".wiki-tree-widget-item[data-nid='" + selectedNid + "'").removeClass("active");
      $widgetItem.closest("#book_explorer_body").find(".wiki-tree-widget-item[data-nid='" + selectedNid + "'] td.book-explorer-element-icon").removeClass("selected-option");
    }
    $widgetItem.find("td.book-explorer-element-icon").addClass("selected-option");
    $widgetItem.addClass("active");
    $widgetItem.closest("#book_explorer_body").attr("data-selected", nid);

    // open parents if item is nested
    Gofast.book.openItemSiblings($widgetItem);
    $widgetItem[0].scrollIntoView({behavior: "smooth", block: "center"});

    // handle form inputs if item is in a form
    $widgetForm = $widgetItem.closest("form");
    if ($widgetForm.length) {
      Gofast.book.updatePageSelector($widgetForm, nid);
      Gofast.book.updateLocationsInput($widgetForm, nid);
    }
  };
    
}(jQuery, Gofast, Drupal));