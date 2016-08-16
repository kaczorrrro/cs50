<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];
    if (!isset($_GET["geo"]))
        return;
    
    $spiltByComma = explode(",",$_GET["geo"]);
    $finished = false;
    //postal code
    foreach ($spiltByComma as $word)
    {
        if ( is_numeric($word[0]) )
        {
            $places = CS50::query("SELECT * FROM places WHERE postal_code LIKE ?", $word . "%");
            if (!empty($places))
            {
                $finished = true;
                break;
            }
                
        }
    }
    
    if ($finished)
    {
        printIt($places);
        return;
    }
        
    
    //place name
    foreach ($spiltByComma as $word)
    {
        $word = $word . "%";
        $temp = CS50::query("SELECT * FROM places WHERE place_name LIKE (?) LIMIT 3",$word);
        if (!empty($temp))
        {
            $places = array_merge($places,$temp);
        }
    }
    
    //admin name
    foreach ($spiltByComma as $word)
    {
        $word = $word . "%";
        $temp = CS50::query("SELECT * FROM places WHERE admin_name1 LIKE (?) LIMIT 3",$word);
        if (!empty($temp))
        {
            $places = array_merge($places,$temp);
        }   
    }
    
    //sorting
    for ($i = 0,$n=count($places);$i<$n;$i++)
    {
        foreach ($spiltByComma as $word)
        {
            if ($places[$i] == $word)
            {
                $temp = $places[$i];
                $places[$i] = $places[0];
                $places[0] = $temp;
            }
        }
    }

    
    printIt($places);


    // TODO: search database for places matching $_GET["geo"], store in $places

    // output places as JSON (pretty-printed for debugging convenience)
    


    function printIt($places)
    {
        header("Content-type: application/json");
        print(json_encode($places, JSON_PRETTY_PRINT));
    }
?>