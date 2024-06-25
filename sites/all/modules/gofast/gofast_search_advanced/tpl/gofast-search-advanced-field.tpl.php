<label><?= $field['title'] ?></label>
<?php if($field['type'] != 'date'): ?>
    <div class="form-field-operator grid-container w-100">
        <select class="custom-select custom-select-sm grid-item-left form-select-field-operator mr-2" style="width:90%">
            <option value="equal">&#x3D; </option>
            <option value="not-equal">&#8800; </option>
        </select>
<?php endif; ?>
<?php switch ($field['type']) {
    case 'input':
        print '<input type="text" class="form-control form-control-sm w-100" name="' . $field['solr_field'] .  '" data-id="advanced-filters-'. $key .'">';
        break;
    case 'select':
        print '<select class="form-control form-control-sm gofast-select2 w-100" name="' . $field['solr_field'] .  '" data-id="advanced-filters-'. $key .'" data-placeholder="Saisir">
        <option></option>';
        foreach ($field['fields'] as $key => $value) :
            if(isset($value['id'])){
                print '<option id="' . $field['solr_field'] . "-" . $value['id'] . '" value="' . $value['id'] . '"> ' . $value['text'] . '</option>';
            }else{
                print '<option id="' . $field['solr_field'] . "-" . $key . '" value="' . $value . '"> ' . $value . '</option>';
            }
        endforeach;
        print '</select>';
        break;
    case 'date':
        print '<div class="grid-container w-100 form-search-date">';
            print '<select class="custom-select custom-select-sm form-select-date form-select-field-operator mr-2" aria-label="" style="width:90%">';
            print '<option value="between" selected>< ></option>';
            print '<option value="lower">></option>';
            print '<option value="higher"><</option>';
            print '</select>';

            print '<div class="input-group">';
                print '<input type="text" class="form-control form-control-sm form-control-date gofastDateRangetimepicker" name="' . $field['solr_field'] .  '" data-id="advanced-filters-'. $key .'"/>';
                print '<span class="input-group-text">';
                    print '<i class="fad fa-calendar fs-1"></i>';
                print '</span>';
            print '</div>';
        print '</div>';
        break;
    case 'tagify':
        print '<div class="w-100">';
            print '<div class="form-control form-control-sm form-tagify w-100" name="' . $field['solr_field'] .  '" id="tags-list-ac">';
                print '<input class="js-tagify text-truncate metadata-node border-0" placeholder="Essayez d\'ajouter des étiquettes depuis la liste" data-taxonomy_term="" data-enforce="" data-vid="' . $field['vid'] . '" data-pk="" type="text" id="edit-field-custom-keywords" data-name="' . $field['name'] . '" name="ac-list-tags-custom-keywords" maxlength="" data-oninput="' . $field['oninput'] . '">';
                print '<input class="gofast_display_none w-100" type="text" id="edit-actagify-ac-list-tags-custom-keywords" name="gofast_tagify_ac">';
            print '</div>';
        print '</div>';
        break;
    case 'auth':
            print '<select class="form-control form-control-sm gofast-select2-ajax w-100" name="' . $field['solr_field'] . '" data-id="advanced-filters-'. $key .'">';
            print '</select>';
        break;
    default:
        # code...
        break; 
} ?>
<?php if($field['type'] != 'date'): ?>
    </div>
<?php endif; ?>

