function CustomGofastMultiAutocompleteCtrl($scope, $parse, $log, widgetNameFactory, $http, $element, $timeout) {
    $scope.loading = false;

    // Create a new Tagify instance
    var inputElement = $element[0].querySelector('#tagInput');

    // Wait for binding (placeholder, name) to occur
    $timeout(function () {
        $scope.ctrl.tagifyInstance = new Tagify(inputElement, {
            whitelist: [], // initial tag list
            enforceWhitelist: true, // do not allow adding value that not in the whitelist
            templates: {
                tag: $scope.ctrl.tagTemplate,
                dropdownItem: $scope.ctrl.suggestionItemTemplate
            },
            dropdown: {
                enabled: 3, // show suggestion after 3 typed character
                maxItems: 50, // maxumum allowed rendered suggestions
                enabled: 1, // show suggestions on focus
                closeOnSelect: true, // hide the suggestions dropdown once an item has been selected
                searchKeys: ['name'] // set by which keys to search for suggestions when typing
            }
        });
        $scope.ctrl.tagifyInstance.on('input', function(e) {
            var value = e.detail.value;
            if (value.length < 3) {
                $scope.ctrl.tagifyInstance.dropdown.hide.call($scope.ctrl.tagifyInstance);
                return;
            }
            $scope.ctrl.getData(value).then(function(response){
                // update the whitelist property
                $scope.ctrl.tagifyInstance.settings.whitelist = [...$scope.ctrl.tagifyInstance.value, ...response];
                // trigger dropdown showing
                $scope.ctrl.tagifyInstance.dropdown.show.call($scope.ctrl.tagifyInstance, value);
            });
        });
    
        $scope.ctrl.tagifyInstance.on('add remove', function(e) {
            $scope.ctrl.setData();
        });
    });

    this.suggestionItemTemplate = function(tagData) {
        var imageData;
        var template;
        template = "<div " + this.getAttributes(tagData) + " class='tagify__dropdown__item' tabindex='0' role='' option''>";
        imageData = "<div class='tagify__tag__avatar-wrap'><i class='" + tagData.icon + " mr-2'></i></div>";
        template += imageData + " <strong>" + tagData.name + "</strong>";
        template += "</div>";
        return template;
    }

    this.tagTemplate = function(tagData) {
        var imageData;
        var text = tagData.name || "";
        tagColorClass = "tagify__tag-light--primary";
        imageData = "<div><i class='"+tagData.icon+" text-primary'></i></div>";
        let removeButton = "<x title='' class='tagify__tag__removeBtn' role='button' aria-label='remove tag'></x>";
        return "<tag title='" + text + "'  contenteditable='false'  spellcheck='false' tabIndex='-1'  class='" + this.settings.classNames.tag + " " + this.getAttributes(tagData) + "'>" + removeButton + "  <div>  " + imageData + "<span class='tagify__tag-text'>" + text + "</span></div></tag>";
    }

    this.getData = function (inputValue) {
        $scope.loading = true;
        return $http.get("../../../../../../../../api/" + $scope.properties.type + "/autocomplete?str=" + inputValue + "&bundles=" + $scope.properties.bundles + "&populate=true").then(function(r){
            return r.data;
        });
    };

    this.setData = function(){
        var tags = $scope.ctrl.tagifyInstance.value;
        $scope.properties.value = tags;
    }

    $scope.$watch(() => $scope.properties.value, function(current, old){
        // init values are given to the input: add matching tags
        if (!old.length && $scope.ctrl.tagifyInstance) {
            $scope.ctrl.tagifyInstance.settings.whitelist = [...$scope.properties.value];
            $scope.ctrl.tagifyInstance.addTags($scope.properties.value);
        }
    });

    this.name = widgetNameFactory.getName('customGofastMultiAutocomplete');
}