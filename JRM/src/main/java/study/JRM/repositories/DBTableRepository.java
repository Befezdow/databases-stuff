package study.JRM.repositories;

import org.springframework.data.repository.CrudRepository;

import study.JRM.entities.DBTable;

public interface DBTableRepository extends CrudRepository<DBTable, Long> {

}
