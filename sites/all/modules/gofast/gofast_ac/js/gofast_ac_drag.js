/**
 * @file
 *
 * Special Tagify instances intended to make drag inputs.
 *
 */

(function ($, Gofast, Drupal) {
  Drupal.behaviors.initDragInput = {
    attach: function (context) {
      if (typeof Tagify == "undefined") {
        return;
      }
      const $dragCandidates = $(".gofast-ac-drag-input:not(.processed)");
      $dragCandidates.addClass("processed").each(function () {
        Gofast.dragInput.init($(this));
      });
    },
  };

  Gofast = Gofast || {};

  Gofast.dragInput = {
    eventCallbacks: {
      dragStart(e) {
        const $target = $(e.target);
        if ($target.hasClass("tagify__tag--model")) {
          e.originalEvent.dataTransfer.setData(
            "text/plain",
            `[[${$target.attr("data-drag")}]]`
          );
          return;
        }
        // If the tag is not a "static" tag, we need to be able to track down the original DOM element in the drop event
        const id = Date.now() + "_" + Math.random().toString(36).substr(2, 9);
        $target.attr("id", id);
        e.originalEvent.dataTransfer.setData(
          "text/plain",
          `${id}||[[${$target.attr("data-drag")}]]`
        );
      },
      drop(e, tagify, $inputElm, $tagifyDOMScope) {
        e.preventDefault();

        // Fallback if no browser support to get caret position
        let cursorPosition = $inputElm.val().length;
        // Get the caret range or position
        let caretPos = null;
        if (document.caretRangeFromPoint) {
          // Webkit specific implementation of the API
          caretPos = document.caretRangeFromPoint(e.clientX, e.clientY);
        } else if (document.caretPositionFromPoint) {
          // Official API
          caretPos = document.caretPositionFromPoint(e.clientX, e.clientY);
        }

        let id = e.originalEvent.dataTransfer.getData("text/plain");

        // If the tag is not a "static" tag, we remove it so the end result is a tag move rather than a tag duplicate
        if (id.includes("||")) {
          let [elementId, targetValue] = id.split("||");
          const $originalTag = $(`#${elementId}`);
          id = targetValue;
          // Remove the tag and update tagify update to update the value of the $inputElm
          $originalTag.trigger("remove")
          tagify.update()
        }
        // The offset of the caret matches the offset of its text node, but the span content may be splitted into several text nodes separated by HTML nodes
        // So we have to add to the offset the length of all the nodes before
        if (caretPos) {
          // Find which child node the caret is within
          const textNode = caretPos.startContainer || caretPos.offsetNode;
          const offset = caretPos.startOffset || caretPos.offset;
          let parentNode = textNode.parentNode;
          if (textNode.nodeType !== Node.TEXT_NODE) {
            parentNode = textNode.closest(".tagify__input");
          }
          const children = Array.from(parentNode.childNodes);
          let offsetInContent = 0;
          for (const child of children) {
            if (child === textNode) {
              cursorPosition = offsetInContent + offset;
              break;
            } else if (child.nodeType === Node.TEXT_NODE) {
              offsetInContent += child.length;
            } else {
              // If it's an HTML element, assume its a tag so get the length of the formatted tag string
              offsetInContent += `[[{"value":"${child.innerText}"}]]`.length;
            }
          }
        }

        let spanContent = $inputElm.val();
        const textBefore = spanContent.substring(0, cursorPosition);
        const textAfter = spanContent.substring(
          cursorPosition,
          spanContent.length
        );

        // We'll insert the current tag value later in case the current tag value is ambiguous with some other tag values
        spanContent = textBefore + "[[ID]]" + textAfter;
        inputContent = spanContent.replace("[[ID]]", id);

        // Leave room for cursor insertion between contiguous tags
        inputContent = inputContent.replace("]][[", "]] [[");

        $inputElm.val(inputContent);
        tagify.loadOriginalValues();
        const tags = $tagifyDOMScope.find("tag:not(.tag-processed)");
        Gofast.dragInput.handlers.attachEvents(tags);
      },
    },
    handlers: {
      toggle(e, $spanElm, $inputContainer) {
        e.stopPropagation();
        const classes = $spanElm.hasClass("d-block")
          ? ["d-block", "d-none"]
          : ["d-none", "d-block"];
        $spanElm.removeClass(classes[0]).addClass(classes[1]);
        $inputContainer.removeClass(classes[1]).addClass(classes[0]);
        // In case the values have been reset before toggle, make sure the events are reattached
        const tags = $inputContainer.find("tag:not(.tag-processed)");
        Gofast.dragInput.handlers.attachEvents(tags);
      },
      async submit(e, $spanElm, $inputContainer, $confirmationButtons) {
        e.stopPropagation();
        const id = $inputContainer.attr("id").replace("gofast-ac-drag-input-", "");
        const value = $inputContainer.find("input").val();
        $inputContainer.css("pointer-events", "none");
        $inputContainer.parent().css("cursor", "not-allowed");
        $confirmationButtons.append($("<div class='spinner'>"));
        const callback = $confirmationButtons.find(".confirmButton").attr("data-submit");
        await $.post(callback, {id, value})
          .done(function (response) {
            response = JSON.parse(response);            
            if (response.message) {
              Gofast.toast(response.message.value, response.message.status)
            }
            if (response.callback) {
              window[response.callback.function](...response.callback.arguments);
            }
          })
          .fail(function(response) {
            if (response.status == 403) {
              Gofast.toast(Drupal.t("Operation not allowed"), "error");
            } else {
              Gofast.toast(Drupal.t("Something went wrong!"), "error");
            }
          });
        $inputContainer.css("pointer-events", "auto");
        $inputContainer.parent().css("cursor", "auto");
        $confirmationButtons.find(".spinner").remove();
        Gofast.dragInput.handlers.toggle(e, $spanElm, $inputContainer);
      },
      attachEvents(tags) {
        for (const tag of tags) {
          const $tag = $(tag);
          $tag.addClass("tag-processed");
          $tag.attr("data-drag", tag.innerText);
          $tag.attr("draggable", true);
          $tag.on("dragstart", Gofast.dragInput.eventCallbacks.dragStart);
        }
      },
    },
    init($dragInput) {
      /** Elements */
      const $spanElm = $dragInput.find("span");
      const $inputContainer = $dragInput.find(".tagify-ac-drag-input");
      const $inputElm = $dragInput.find("input");
      const originalValue = $inputElm.val();
      const $confirmationButtons = $dragInput.find(
        ".editableInputConfirmationButtons"
      );
      const $clearButton = $confirmationButtons.find(".clearButton");
      const $confirmButton = $confirmationButtons.find(".confirmButton");
      const $cancelButton = $confirmationButtons.find(".cancelButton");
      const tagify = new Tagify($inputElm[0], {
        id: $dragInput.attr("id"),
        mode: "mix",
        duplicates: true,
        editTags: false,
      });
      const $tagifyDOMScope = $(tagify.DOM.scope);
      const $tagifyDOMInput = $(tagify.DOM.input);

      $spanElm.on("click", (e) =>
        Gofast.dragInput.handlers.toggle(e, $spanElm, $inputContainer)
      );
      $clearButton.on("click", (e) => {
        e.stopPropagation();
        $inputElm.val("");
        tagify.loadOriginalValues();
        $confirmButton.click();
      });
      $cancelButton.on("click", (e) => {
        $inputElm.val(originalValue);
        tagify.loadOriginalValues();
        Gofast.dragInput.handlers.toggle(e, $spanElm, $inputContainer)
      });
      $confirmButton.on("click", (e) =>
        Gofast.dragInput.handlers.submit(e, $spanElm, $inputContainer, $confirmationButtons)
      );

      /** Attach relevant events to the elements */
      const allValues = [];
      const $tags = $dragInput.find("tag");
      // Attach events to "static" tags
      Gofast.dragInput.handlers.attachEvents($tags);
      for (const draggable of $tags) {
        const $draggable = $(draggable);
        const key = $draggable.attr("data-drag");
        if (!key) {
          continue;
        }
        allValues[key] = key;
      }

      $tagifyDOMScope.on("dragenter", (e) => e.preventDefault());
      $tagifyDOMScope.on("drop", (e) =>
        Gofast.dragInput.eventCallbacks.drop(e, tagify, $inputElm, $tagifyDOMScope)
      );

      // Make sure no drop event is triggered from the drag input container's padding
      $dragInput.parent().parent().on("drop", (e) => {
        e.preventDefault();
        e.stopPropagation();
      });

      // Do not allow to jump lines
      $tagifyDOMInput.on("keydown", (e) => {
        if (e.keyCode == 13) {
          e.preventDefault();
        }
      });
    },
  };
})(jQuery, Gofast, Drupal);
