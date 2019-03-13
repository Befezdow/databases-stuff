package study.JRM.repositories;

import org.springframework.data.repository.CrudRepository;

import study.JRM.entities.Manager;

public interface ManagerRepository extends CrudRepository<Manager, Long> {
	Manager findOneByFirstName(String firstname);
}
