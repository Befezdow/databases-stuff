package study.JRM.repositories;

import org.springframework.data.repository.CrudRepository;

import study.JRM.entities.Chair;

public interface ChairRepository extends CrudRepository<Chair, Long> {

}