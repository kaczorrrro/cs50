<?php

    // configuration
    require("../includes/config.php"); 

    // render portfolio
    $rows = CS50::query("SELECT * FROM userStocks WHERE user_id = ?",$_SESSION['id']);
    $cash = getMoney();
    
   
    for ($i = 0, $n=count($rows);$i<$n;$i++ )
    {
        $price = lookup($rows[$i]["symbol"])["price"];
        if ($price != 0)
            $rows[$i]["price"] = number_format($rows[$i]["shares"] * $price,4);
        else
            $rows[$i]["price"] = "Stock not found";
    }
    
    render("portfolio.php", ["title" => "Portfolio", "positions" => $rows, "cash"=> number_format($cash,4)]);

?>
