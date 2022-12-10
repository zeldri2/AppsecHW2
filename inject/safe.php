<?php

/**
  * Function to query clients based on phone number
  */
require "config.php";
require "common.php";

if (isset($_POST['submit'])) {
  try {
    $connection = new PDO($dsn, $username, $password, $options);

    $sql = "SELECT *
    FROM users
    WHERE userID = :userID";

    $userID = $_POST['userID'];

    $statement = $connection->prepare($sql);
    $statement->bindParam('userID', $userID, PDO::PARAM_STR);
    $statement->execute();

    $result = $statement->fetchAll();
  } catch(PDOException $error) {
    echo $sql . "<br>" . $error->getMessage();
  }
}
?>

<h2>Find A User by entering their user ID</h2>

<form method="post">
  <label for="userID">User ID</label>
  <input type="text" id="userID" name="userID">
  <input type="submit" name="submit" value="View Results">
</form>

<?php
if (isset($_POST['submit'])) {
  if ($result && $statement->rowCount() > 0) { ?>
    <h2>Results</h2>

    <table>
      <thead>
<tr>
  <th>UserID</th>
  <th>Username</th>
  <th>Password</th>
</tr>
      </thead>
      <tbody>
  <?php foreach ($result as $row) { ?>
      <tr>
        <td><?php echo escape($row["userID"]); ?></td>
        <td><?php echo escape($row["username"]); ?></td>
        <td><?php echo escape($row["password"]); ?></td>
      </tr>
    <?php } ?>
      </tbody>
  </table>
  <?php } else { ?>
    > No results found for <?php echo escape($_POST['userID']); ?>.
  <?php }
} ?>
