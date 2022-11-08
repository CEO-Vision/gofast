/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
(function ($, Gofast, Drupal) {
    console.log("workflow");
    $(document).ready(function() {
            var node = Gofast.get('node');
            console.log(node);
            Drupal.gofast_workflows.gofastWorkflowGetIconNode(node.id);
 });


})(jQuery, Gofast, Drupal);

