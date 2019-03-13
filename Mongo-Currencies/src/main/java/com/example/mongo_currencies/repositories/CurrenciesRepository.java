package com.example.mongo_currencies.repositories;

import com.example.mongo_currencies.models.Currency;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface CurrenciesRepository extends MongoRepository<Currency, String>, AggregatedCurrenciesDataRepository {

}