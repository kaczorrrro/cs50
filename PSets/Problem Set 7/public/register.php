<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"]))
        {
            apologize("Empty username");
        }
        if (empty($_POST["password"]) )
        {
            apologize("Empty password");
        }
        if ($_POST["password"] != $_POST["check"] )
        {
            apologize("Passwords are different");
        }
        
        $rows = CS50::query("SELECT * FROM users WHERE username = ?",$_POST["username"]);
        if (!empty($rows))
        {
            apologize("Name taken");
        }
        
        CS50::query( "INSERT INTO users (username, hash, cash) VALUES (?,?,10000.0)", $_POST['username'], password_hash($_POST["password"],PASSWORD_DEFAULT));
    
        $rows = CS50::query("SELECT * FROM users WHERE username = ?",$_POST["username"]);
        if (!empty($rows))
        {
            $_SESSION["id"] = $rows[0]["id"];
            redirect("/");
        }
        else
        {
            apologize("Something went wrong");
        }
    }

?>