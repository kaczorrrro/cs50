<table class="table">
    <tr>
        <td>Action</td>
        <td>Symbol</td>
        <td>Shares</td>
        <td>Price per share</td>
        <td>Date</td>
    </tr>
    
    <?php foreach($rows as $row): ?>
    <tr class ="<?=$row["color"]?>"   >
        <td><?=$row['action']?></td>
        <td><?=$row['symbol']?></td>
        <td><?=$row['shares']?></td>
        <td><?=$row['price_per_share']?></td>
        <td><?=$row['date']?></td>
    </tr>
    <?php endforeach ?>
    
</table>