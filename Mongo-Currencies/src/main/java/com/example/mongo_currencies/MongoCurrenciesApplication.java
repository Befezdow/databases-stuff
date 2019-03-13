package com.example.mongo_currencies;

import com.example.mongo_currencies.models.Currency;
import com.example.mongo_currencies.repositories.CurrenciesRepository;
import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.ss.usermodel.Row;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.io.FileInputStream;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Scanner;

@SpringBootApplication
public class MongoCurrenciesApplication implements CommandLineRunner {

    private Logger LOGGER = LoggerFactory.getLogger(this.getClass());
    private CurrenciesRepository repository;

    MongoCurrenciesApplication(CurrenciesRepository repository) {
        this.repository = repository;
    }

	public static void main(String[] args) {
		SpringApplication.run(MongoCurrenciesApplication.class, args);
	}

    @Override
    public void run(String... args) {
        startUI();
    }

    private void startUI() {

        SimpleDateFormat formatter = new SimpleDateFormat("dd.MM.yyyy");
        System.out.println("Enter an empty string to stop.");
        Scanner in = new Scanner(System.in);

        while (true) {

            try {
                System.out.print("Date from: ");
                String temp = in.nextLine();
                if (temp.isEmpty()) {
                    return;
                }
                Date dateFrom = formatter.parse(temp);

                System.out.print("Date to: ");
                temp = in.nextLine();
                if (temp.isEmpty()) {
                    return;
                }
                Date dateTo = formatter.parse(temp);

                System.out.println("Results:");
                repository.getCurrenciesInfo(dateFrom, dateTo).forEach(elem -> {
                    System.out.println(elem.toString());
                });
            } catch (ParseException exception) {
                System.out.println("Incorrect date input. Please, try again.");
            }
        }
    }

	private void loadCurrenciesData(String[] currenciesNames) throws Throwable {
        HSSFWorkbook myExcelBook = new HSSFWorkbook(new FileInputStream("/home/befezdow/Workspace/study/Bondin stuff/Befezdow/mongo_currencies/currencies.xls"));
        List<Currency> newList = new ArrayList<>();
        for(String sheet : currenciesNames) {
            HSSFSheet myExcelSheet = myExcelBook.getSheet(sheet);
            for (Row row : myExcelSheet) {
                Date date;
                double rate = 0.0;

                if (row.getCell(0).getCellType() == HSSFCell.CELL_TYPE_NUMERIC) {
                    date = row.getCell(0).getDateCellValue();
                } else {
                    continue;
                }

                if (row.getCell(2).getCellType() == HSSFCell.CELL_TYPE_NUMERIC) {
                    rate = row.getCell(2).getNumericCellValue();
                } else {
                    continue;
                }

                if (rate == 0.0 ) {
                    continue;
                }
                Currency newCur = new Currency(sheet + "/RUB", date, rate);
                newList.add(newCur);
            }
        }
        this.repository.deleteAll();
        this.repository.insert(newList);
        myExcelBook.close();
    }

    public void initDBData() {
        String[] names = { "USD" , "EUR" , "AUD", "TRY" , "SEK", "RON"};
        try {
            this.loadCurrenciesData(names);
        } catch (Throwable error) {
            LOGGER.error(error.getMessage());
        }
    }
}
