package study.JRM.services;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.transaction.Transactional;

import org.springframework.beans.factory.annotation.Autowired;

import study.JRM.entities.Room;
import study.JRM.repositories.RoomRepository;
import study.JRM.support.JRMSupport;

public class RoomServiceImpl implements RoomService {
	
	@Autowired
	private RoomRepository repository;
	
	@PersistenceContext
	private EntityManager entityManager;
	
	@Override
	public void showAll() {

		repository.findAll().forEach(elem -> {
			System.out.println(elem);
		});
	}

	@Override
	@Transactional
	public void showOne() {

		List<Room> allRooms = new ArrayList<Room>();
		repository.findAll().forEach(elem -> {
			allRooms.add(elem);
			System.out.printf("%d) %s\n", allRooms.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);

		int room = JRMSupport.readMenuChoice(in, allRooms.size(), "Index: ");
		if (room == -1) {
			return;
		}
		
		Room neededRoom = allRooms.get(room);
		System.out.printf("Name: %s\n", neededRoom.getName());
		System.out.printf("Description: %s\n", neededRoom.getDescription());
		System.out.printf("Chairs:\n");
		neededRoom.getChairs().forEach(elem -> {
			System.out.printf("\tWeight: %f, Is fragile: %b, Material: %s, Is collapsible: %b, Chair type: %s, Max weight: %f, Room: %s\n",
					elem.getWeight(), elem.isFragile(), elem.getMaterial(), elem.isCollapsible(), elem.getChairType(), elem.getMaxWeight(), elem.getRoom().getName());
		});
		System.out.printf("Tables:\n");
		neededRoom.getTables().forEach(elem -> {
			System.out.printf("\tWeight: %f, Is fragile: %b, Material: %s, Is collapsible: %b, Table type: %s, Height:%f, Room: %s\n",
					elem.getWeight(), elem.isFragile(), elem.getMaterial(), elem.isCollapsible(), elem.getTableType(), elem.getHeight(), elem.getRoom().getName());
		});
		System.out.printf("Monitors:\n");
		neededRoom.getMonitors().forEach(elem -> {
			System.out.printf("\tWeight: %f, Is fragile: %b, Manufacturer: %s, Resolution: %b, Matrix type: %s, Room: %s\n",
					elem.getWeight(), elem.isFragile(), elem.getManufacturer(), elem.getResolution(), elem.getMatrixType(), elem.getRoom().getName());
		});
		System.out.printf("Mice:\n");
		neededRoom.getMice().forEach(elem -> {
			System.out.printf("\tWeight: %f, Is fragile: %b, Manufacturer: %s, Buttons count: %b, Is wireless: %s, Room: %s\n",
					elem.getWeight(), elem.isFragile(), elem.getManufacturer(), elem.getButtonsCount(), elem.isWireless(), elem.getRoom().getName());
		});
	}

	@Override
	@Transactional
	public void addOne() {

		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);
		
		Room room;
		try {
			System.out.print("Name : ");
			String name = in.nextLine();
			System.out.print("Description : ");
			String description = in.nextLine();
			
			room = new Room();
			room.setName(name);
			room.setDescription(description);
		} catch (Throwable t) {
			System.out.println("Incorrect input");
			return;
		}
		
		entityManager.persist(room);
	}

	@Override
	public void deleteOne() {

		List<Room> allRooms = new ArrayList<Room>();
		repository.findAll().forEach(elem -> {
			allRooms.add(elem);
			System.out.printf("%d) %s\n", allRooms.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);

		int room = JRMSupport.readMenuChoice(in, allRooms.size(), "Index: ");
		if (room == -1) {
			return;
		}

		repository.delete(allRooms.get(room));
	}

	@Override
	@Transactional
	public void updateOne() {
		
		List<Room> allRooms = new ArrayList<Room>();
		repository.findAll().forEach(elem -> {
			allRooms.add(elem);
			System.out.printf("%d) %s\n", allRooms.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);

		int room = JRMSupport.readMenuChoice(in, allRooms.size(), "Index: ");
		if (room == -1) {
			return;
		}
		
		Room neededRoom = allRooms.get(room);
		
		System.out.print("Choose option:\n");
		System.out.print("1) Change name\n");
		System.out.print("2) Change description\n");
		System.out.print("3) Go back\n");
		
		boolean exitFlag = false;
		while (!exitFlag) {
			try {
				int choice = Integer.parseInt(in.nextLine());
				switch(choice) {
				case 1:
					System.out.print("New name: ");
					neededRoom.setName(in.nextLine());
					exitFlag = true;
					break;
				case 2:
					System.out.print("New description: ");
					neededRoom.setDescription(in.nextLine());
					exitFlag = true;
					break;
				case 3:
					return;
				default:
					break;
				}
			} catch (Throwable t) {
				System.out.println("Incorrect input");
				return;
			}
		}
		
		entityManager.merge(neededRoom);
	}
}
