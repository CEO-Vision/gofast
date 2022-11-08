// Register the plugin in the editor.
CKEDITOR.plugins.add('gofast_autotag', {
    requires: 'autocomplete,textmatch',

    init: function (editor) {
        editor.on('instanceReady', function () {
            var config = {};

            // Called when the user types in the editor or moves the caret.
            // The range represents the caret position.
            function textTestCallback(range) {
                // You do not want to autocomplete a non-empty selection.
                if (!range.collapsed) {
                    return null;
                }

                // Use the text match plugin which does the tricky job of performing
                // a text search in the DOM. The "matchCallback" function should return
                // a matching fragment of the text.
                return CKEDITOR.plugins.textMatch.match(range, matchCallback);
            }

            // Returns the position of the matching text.
            // It fetches a word after using a '@' character
            // up to the caret position.
            function matchCallback(text, offset) {
                // Get the text before the caret.
                var left = text.slice(0, offset),
                        // Will look for a '@' character followed by a username.
                        //The '@' char can't have a letter or the AC won't work
                        match = left.match(/(?<!([a-zA-Z]))(@[a-zA-Z]*)(?!@)/);

                if (!match) {
                    return null;
                }
                return {
                    start: match.index,
                    end: offset
                };
            }

            config.textTestCallback = textTestCallback;

            //We get all users we can access and store it in an array that will be used for the ac
            var usersArray = {};
            var itemsArray = [];

            var nid = Drupal.settings.gofast.node.id;

            $.ajax({
                type: "GET",
                url: window.origin + "/gofast_og/" + nid + "/get_parents",
                success: function (gids) {
                    debugger;
                    gids = JSON.parse(gids);
                    $.each(gids, function (gid) {
                        $.ajax({
                            url: window.origin + "/gofast/get/user_from_space/" + gid,
                        })
                            .done(function (data) {
                                debugger;
                                usersArray = data;
                                for (var i = 0; i < usersArray.length; i++) {
                                    uid = parseInt(usersArray[i]["value"], 10);
                                    if(itemsArray[uid] == undefined){
                                        itemsArray[uid] = {
                                            uid: uid,
                                            id: usersArray[i]["name"],
                                            displayname: usersArray[i]["display_name"],
                                            picture: usersArray[i]["avatar"]
                                        }
                                    }
                                }
                            });
                    });


                }
            });


            // Returns (through its callback) the suggestions for the current query.
            function dataCallback(matchInfo, callback) {
                // Remove the '#' tag.
                var query = matchInfo.query.substring(1);

                // Simple search.
                // Filter the entire items array so only the items that start
                // with the query remain.
                var suggestions = itemsArray.filter(function (item) {
                    return String(item.displayname.toLowerCase()).indexOf(query) == 0;
                });

                // Note: The callback function can also be executed asynchronously
                // so dataCallback can do an XHR request or use any other asynchronous API.
                callback(suggestions);
            }

            config.dataCallback = dataCallback;

            // Define the templates of the autocomplete suggestions dropdown and output text.
            config.itemTemplate = "<li data-id=\"{id}\" class=\"gofast__comment-taglist-elem\">\n<div class=\"gofast__comment-taglist-icon\"> <img src=\"{picture}\"/>\n</div>\n<div class=\"gofast__comment-taglist-user\"> <strong>{displayname}</strong><br/> <span>{id}</span>\n</div>\n</li>";
            config.outputTemplate = "<a contenteditable=\"false\" class=\"gofast__comment-tag text-nowrap\" href=\"" + window.location.origin + "/user/{uid}\" id=\"user-autocomplete-{uid}\">\n<img class=\"gofast__comment-tag-icon\" src=\"{picture}\"/>\n<span class=\"gofast__comment-tag-text\">{displayname}</span>\n</a>" + "&nbsp;";

            // Attach autocomplete to the editor.
            new CKEDITOR.plugins.autocomplete(editor, config);
        });
    }
});
