<form action="sell.php" method = "POST">
    <select name="symbol">
        
        <option value ="" > </option>
        
        <?php foreach($names as $name):?>
        
            <option value = <?=$name?> > <?=$name?> </option>
            
        <?php endforeach ?>
    </select>
    <input type="submit" value="Sell all"/>
</form>