<table>
    <tr>
        <td style="width: 30px;">
            <i class="fa fa-arrow-right" style="color: #337ab7;"></i> 
        </td>
        <td>
            <?php echo t("GoFAST Integrity status : ", array(), array("context" => "gofast:gofast_integrity")) . $run_state ?>
        </td>
    </tr>
    
    <tr>
        <td style="width: 30px;">
            <i class="fa fa-clock-o" style="color: #337ab7;"></i> 
        </td>
        <td>
            <?php echo $time_range; ?>
        </td>
    </tr>
    
    <tr>
        <td style="width: 30px;">
            <i class="fa fa-calendar" style="color: #337ab7;"></i> 
        </td>
        <td>
            <?php echo t("Current week : ", array(), array("context" => "gofast:gofast_integrity")) . $current_week; ?>
        </td>
    </tr>
</table>