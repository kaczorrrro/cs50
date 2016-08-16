<?php
  
    require("../includes/config.php");
  
    if ($_SERVER['REQUEST_METHOD'] == "GET")
    {
        $rows = CS50::query("SELECT * FROM userStocks WHERE user_id = ?", $_SESSION["id"]);
        $stocks = [];
        foreach ($rows as $row)
        {
            $stocks[] = $row['symbol'];
        }
        
        
        render("sell_form.php",["names" => $stocks]);
    }
    else if ($_SERVER["REQUEST_METHOD"] = "POST")
    {
        $symbol = $_POST["symbol"];
        if (empty($symbol))
            apologize("Choose stock to sell");
            
        $row = CS50::query("SELECT * FROM userStocks WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        if (empty($row))
            apologize("error");
            
        $price = lookup($symbol) ["price"];
        $number = $row[0]["shares"];
        
        if ($price == 0)
            apologize("error");
        
        $cash = $number *$price;
        

        $returned = CS50::query( "START TRANSACTION;
         DELETE FROM userStocks WHERE user_id = ? AND symbol = ?;
        UPDATE users SET cash = cash + $cash WHERE id = ?;
        COMMIT", $_SESSION["id"], $_POST["symbol"], 
        $_SESSION["id"] );
        
        $date = date("Y-m-d G:i:s");
        CS50::query("INSERT INTO history (user_id,bought,symbol, shares,price_per_share,date)
        VALUES ( {$_SESSION["id"]} , 0 , \"$symbol\" , $number , $price , ?) ",$date );


        render("success.php");
            
    }
      
?>