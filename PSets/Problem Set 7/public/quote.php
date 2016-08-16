<?php

    // configuration
    require("../includes/config.php"); 

    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("quote_form.php", ["title" => "Quote"]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["symbol"]);
        
        if (empty($stock))
            apologize("Stock name not found");
        $name = $stock["name"];
        $symbol = $stock["symbol"];
        $price = number_format($stock["price"],4);
        render("quote_show.php", ["title" => "Quote","name" => $name,"symbol" => $symbol, "price" => $price]);
    }
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio"]);

?>
