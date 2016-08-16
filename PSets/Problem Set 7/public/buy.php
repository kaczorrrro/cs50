<?php
    require("../includes/config.php");
    if ($_SERVER['REQUEST_METHOD'] == "GET")
    {
        render("buy_form.php");
    }
    else
    {
       
        $number = $_POST["shares"];
        
        if (empty($_POST["symbol"]))
            apologize("No symbol");
        else if (empty($number) || $number <= 0)
            apologize("Wrong number");
        
        $symbol = strtoupper($_POST["symbol"]);
        
        $costPerShare = lookup($symbol) ["price"];
        
        if ($costPerShare == 0)
            apologize("Stock not found");
        
        $money = getMoney();
        
        if ($costPerShare*$number > $money)
            apologize("Too poor for that");
        
        $state = CS50::query("INSERT INTO userStocks (user_id, symbol, shares) VALUES ({$_SESSION['id']},?,$number)
        ON DUPLICATE KEY UPDATE shares = shares + $number", $symbol);
        
        CS50::query("UPDATE users SET cash = cash - $costPerShare*$number WHERE id = {$_SESSION["id"]}");
        
        $date = date("Y-m-d G:i:s");
        CS50::query("INSERT INTO history (user_id,bought,symbol,shares,price_per_share,date)
        VALUES ( {$_SESSION["id"]} , 1 , \"$symbol\",  $number , $costPerShare , ?) ",$date );
        
        
        if ($state === false)
            apologize("error");
            
        render("success.php");    
        
        
    }
?>