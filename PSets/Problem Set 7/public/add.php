<?php
    require("../includes/config.php");
    
    
    if( !isset($_GET["cash"]) )
    {
        render("add_form.php");
    }
    else
    {
        $cash = $_GET["cash"];

        if ((int)$cash <= 0)
            apologize("Wrong amount");
        
        CS50::query("UPDATE users SET cash = cash + $cash WHERE id = {$_SESSION["id"]}");
        render("success.php");
    }
?>