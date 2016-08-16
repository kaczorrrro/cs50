<table class="table table-bordered">
    <tr>
        <td>Symbol</td>
        <td>Shares</td>
        <td>Value</td>
    </tr>
<?php foreach ($positions as $position): ?>

    <tr>
        <td><?= $position["symbol"] ?></td>
        <td><?= $position["shares"] ?></td>
        <td><?= $position["price"] ?></td>
    </tr>

<?php endforeach ?>

        <tr>
        <td>Money</td>
        <td></td>
        <td> <?=$cash?>  </td>
    </tr>
</table>