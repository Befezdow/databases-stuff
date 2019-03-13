package com.sqlredislogs.SQLRedisLogs;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import redis.clients.jedis.Jedis;

import java.sql.*;
import java.util.List;
import java.util.Scanner;

@SpringBootApplication
public class SqlRedisLogsApplication implements CommandLineRunner {

    private static final Logger LOGGER = LoggerFactory.getLogger(SqlRedisLogsApplication.class);
    private Connection psqlConnection;
    private Jedis jedis;

	public static void main(String[] args) {
		SpringApplication.run(SqlRedisLogsApplication.class, args);
	}

	@Override
	public void run(String ...args) {

		connectToPostgres();
		connectToRedis();

        Scanner in = new Scanner(System.in);
        StringBuilder builder = new StringBuilder();
        System.out.println("Enter an empty string to stop.");
		while (true) {

            System.out.print("=> ");
		    String temp = in.nextLine();
		    if (temp.isEmpty()) {
		        break;
            }
            builder.append(temp);

		    if (temp.contains(";")) {
		        if (builder.toString().trim().toLowerCase().startsWith("select")) {
                    executeQuery(builder.toString());
                } else {
		            System.out.println("Only selects are available");
                }
		        builder.setLength(0);
            }
        }

        clearRedis();
		disconnectFromPostgres();
		disconnectFromJedis();
	}

	private void connectToPostgres() {

	    try {

			psqlConnection = DriverManager.getConnection("jdbc:postgresql://localhost:5432/test", "redis_client", "rediska");
			LOGGER.debug("Postgres is connected!");
		} catch ( Exception e ) {

			LOGGER.error(e.getClass().getName() + ": " + e.getMessage());
			System.exit(1);
		}
	}

	private void disconnectFromPostgres() {

	    try {

            psqlConnection.close();
            LOGGER.debug("Postgres is disconnected!");
        } catch ( Exception e ) {

            LOGGER.error(e.getClass().getName() + ": " + e.getMessage());
            System.exit(1);
        }
    }

    private void connectToRedis() {

        jedis = new Jedis("localhost");
        LOGGER.debug("Redis is connected: PING-" + jedis.ping());
    }

    private void disconnectFromJedis() {
	    jedis.close();
    }

    private void clearRedis() {
        jedis.del("sql-requests");
    }

	private void executeQuery(String query) {

	    try {

	        String fromRedis = jedis.hget("sql-requests", query);
	        if (fromRedis == null) {

                Statement stmt = psqlConnection.createStatement();

                ResultSet results = stmt.executeQuery(query);
                ResultSetMetaData metaData = results.getMetaData();

                String union = "";
                StringBuilder builder = new StringBuilder(union);

                for (int i = 1; i <= metaData.getColumnCount(); ++i) {

                    builder.append(metaData.getColumnName(i));
                    if (i != metaData.getColumnCount()) {
                        builder.append('\t');
                    } else {
                        builder.append('\n');
                    }
                }

                while (results.next()) {

                    for(int i = 1; i <= metaData.getColumnCount(); ++i) {

                        builder.append(results.getString(i));
                        if (i != metaData.getColumnCount()) {
                            builder.append('\t');
                        }
                    }
                    if (!results.isLast()) {
                        builder.append('\n');
                    }
                }
                jedis.hset("sql-requests", query, builder.toString());
                System.out.println(builder.toString());

                stmt.close();
            } else {
	            System.out.println(fromRedis);
            }
        } catch ( Exception e ) {

            System.out.println(e.getMessage());
        }
    }
}
