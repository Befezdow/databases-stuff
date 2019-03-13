package com.example.mongo_currencies.repositories;

import com.example.mongo_currencies.models.AggregatedCurrenciesData;

import java.util.Date;
import java.util.List;

public interface AggregatedCurrenciesDataRepository {

    List<AggregatedCurrenciesData> getCurrenciesInfo(Date dateFrom, Date dateTo);
}
