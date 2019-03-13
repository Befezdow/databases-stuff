package com.example.mongo_currencies.repositories;

import com.example.mongo_currencies.models.AggregatedCurrenciesData;
import org.springframework.data.mongodb.core.MongoTemplate;
import org.springframework.data.mongodb.core.aggregation.Aggregation;
import org.springframework.data.mongodb.core.aggregation.GroupOperation;
import org.springframework.data.mongodb.core.aggregation.MatchOperation;
import org.springframework.data.mongodb.core.query.Criteria;

import java.util.Date;
import java.util.List;

import static org.springframework.data.mongodb.core.aggregation.Aggregation.group;
import static org.springframework.data.mongodb.core.aggregation.Aggregation.match;

public class AggregatedCurrenciesDataRepositoryImpl implements AggregatedCurrenciesDataRepository {

    private final MongoTemplate mongoTemplate;

    AggregatedCurrenciesDataRepositoryImpl(MongoTemplate mongoTemplate) {
        this.mongoTemplate = mongoTemplate;
    }

    @Override
    public List<AggregatedCurrenciesData> getCurrenciesInfo(Date dateFrom, Date dateTo) {

        MatchOperation match = match(Criteria.where("date").gte(dateFrom).andOperator(Criteria.where("date").lte(dateTo)));
        GroupOperation group = group("name").max("rate").as("maxValue").min("rate").as("minValue").avg("rate").as("avgValue");

        return mongoTemplate.aggregate(Aggregation.newAggregation(match, group),"list", AggregatedCurrenciesData.class).getMappedResults();
    }
}
