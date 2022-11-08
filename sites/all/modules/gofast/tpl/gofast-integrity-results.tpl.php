<table>
    <tr>
        <td style="width: 20px;">
            <i class="fa fa-times" style="color: #c0392b;"></i> 
        </td>
        <td>
            <?php echo count($results) . " " . t(" invalid elements found", array(), array("context" => "gofast:gofast_integrity"))?>
        </td>
    </tr>
    <tr>
        <td style="width: 20px;">
            <i class="fa fa-info-circle" style="color: #337ab7;"></i> 
        </td>
        <td>
            <?php echo t("These results are displayed in a programmatically exploitable format. You may contact your administrator to exploit them.", array(), array("context" => "gofast:gofast_integrity"))?>
        </td>
    </tr>
</table>

<pre>
    <?php echo print_r($results); ?>
</pre>