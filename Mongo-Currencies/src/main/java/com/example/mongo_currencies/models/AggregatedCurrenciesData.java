package com.example.mongo_currencies.models;

public class AggregatedCurrenciesData {

    private String id;

    private float maxValue;

    private float minValue;

    private float avgValue;

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public float getMaxValue() {
        return maxValue;
    }

    public void setMaxValue(float maxValue) {
        this.maxValue = maxValue;
    }

    public float getMinValue() {
        return minValue;
    }

    public void setMinValue(float minValue) {
        this.minValue = minValue;
    }

    public float getAvgValue() {
        return avgValue;
    }

    public void setAvgValue(float avgValue) {
        this.avgValue = avgValue;
    }

    @Override
    public String toString() {
        return String.format("Name: %s, Min. value: %f, Avg. value: %f, Max. value: %f", this.id, this.minValue, this.avgValue, this.maxValue);
    }
}
