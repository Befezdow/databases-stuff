package study.JRM.repositories;

import org.springframework.data.repository.CrudRepository;

import study.JRM.entities.Room;

public interface RoomRepository extends CrudRepository<Room, Long> {
	Room findOneByName(String name);
}
