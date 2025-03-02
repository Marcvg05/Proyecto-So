#include <stdio.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Database connection details
    char *server = "localhost";
    char *user = "root";
    char *password = "yourpassword"; // Replace with your MySQL password
    char *database = "yourdatabase"; // Replace with your database name

    // Initialize connection
    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    // Query to retrieve matches where player with ID 1 won
    if (mysql_query(conn, "SELECT m.match_id, m.match_date, m.duration FROM matches m WHERE m.winner_id = 1")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    // Store the result
    res = mysql_use_result(conn);

    // Print the results
    printf("Matches where player 1 won:\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("Match ID: %s, Date: %s, Duration: %s minutes\n", row[0], row[1], row[2]);
    }

    // Free the result and close the connection
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}