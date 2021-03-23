package com.marian;


import com.mashape.unirest.http.JsonNode;
import com.mashape.unirest.http.Unirest;
import com.mashape.unirest.http.exceptions.UnirestException;
import org.json.JSONArray;

import java.io.FileWriter;
import java.io.IOException;

public class Main {
    private static FileWriter fileWriter;


    public static void main(String[] args) throws UnirestException, IOException {
        if (args[0] != null) {
            fileWriter = new FileWriter(args[0]);
        } else throw new RuntimeException("file error");

        for (int i = 0; i < 1; i++) {
            fetchAPIData();
        }

    }

    private static void fetchAPIData() throws UnirestException {
        JsonNode jsonNodeHttpResponse = Unirest.get("https://qrng.anu.edu.au/API/jsonI.php?length=1000&type=uint16&size=1024")
                .asJson().getBody();
        JSONArray data = jsonNodeHttpResponse.getObject().getJSONArray("data");


        data.forEach(value -> {
            try {
                fileWriter.write(String.valueOf(value) + "\n");
                fileWriter.flush();
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
    }
}
