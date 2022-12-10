<?php

/**
  * Function to query clients based on phone number
  */
require "common.php";

if (isset($_POST['submit'])) {
  $userID = $_POST['userID'];

  $mysqli = new mysqli('localhost', 'root', 'password', 'injection');

  if ($mysqli->connect_errno){
        printf("Connect failed: %s\n", $mysqli->connect_error);
        exit();
  }

  $sql = "SELECT * FROM users WHERE userID = $userID";
  $result = $mysqli->query($sql);
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
  if ($result) { ?>
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
