package study.JRM.repositories;

import org.springframework.data.repository.CrudRepository;

import study.JRM.entities.Mouse;

public interface MouseRepository extends CrudRepository<Mouse, Long> {

}
