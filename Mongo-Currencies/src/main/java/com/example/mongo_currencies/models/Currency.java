package com.example.mongo_currencies.models;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.index.IndexDirection;
import org.springframework.data.mongodb.core.index.Indexed;
import org.springframework.data.mongodb.core.mapping.Document;

import java.util.Date;

@Document(collection = "list")
public class Currency {

    @Id
    private String id;

    private String name;

    @Indexed(direction = IndexDirection.ASCENDING)
    private Date date;

    @Indexed(direction = IndexDirection.ASCENDING)
    private double rate;

    public Currency() {}

    public Currency(String name, Date date, double rate) {

        this.name = name;
        this.date = date;
        this.rate = rate;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public double getRate() {
        return rate;
    }

    public void setRate(double rate) {
        this.rate = rate;
    }

    @Override
    public String toString() {
        return String.format("Id: %s, Name: %s, Date: %s, Rate: %f", id, name, date, rate);
    }
}
