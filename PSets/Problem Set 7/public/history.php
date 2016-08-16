<?php
    require("../includes/config.php");
    
    $rows = CS50::query("SELECT * FROM history WHERE user_id = {$_SESSION['id']} ORDER BY id DESC");
    
    for($i = 0, $n = count($rows); $i<$n; $i++)
    {
        $rows[$i]["color"] = ($rows[$i]["bought"]==1)?"bg-success":"bg-warning";
        $rows[$i]["action"] = ($rows[$i]["bought"]==1)?"Buy":"Sell";
    }
    
    render("history_form.php",["rows" => $rows]);
    
?>