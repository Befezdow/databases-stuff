package study.JRM.services;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.transaction.Transactional;

import org.springframework.beans.factory.annotation.Autowired;

import study.JRM.entities.Manager;
import study.JRM.entities.Mouse;
import study.JRM.entities.Room;
import study.JRM.repositories.ManagerRepository;
import study.JRM.repositories.MouseRepository;
import study.JRM.repositories.RoomRepository;
import study.JRM.support.JRMSupport;

public class MouseServiceImpl implements MouseService {
	
	@Autowired
	private MouseRepository mouseRepository;
	
	@Autowired
	private ManagerRepository managerRepository;
	
	@Autowired
	private RoomRepository roomRepository;
	
	@PersistenceContext
	private EntityManager entityManager;

	@Override
	public void showAll() {

		mouseRepository.findAll().forEach(elem -> {
			System.out.println(elem);
		});
		
	}

	@Override
	public void showOne() {

		List<Mouse> allMice = new ArrayList<Mouse>();
		mouseRepository.findAll().forEach(elem -> {
			allMice.add(elem);
			System.out.printf("%d) %s\n", allMice.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);
		
		int mouse = JRMSupport.readMenuChoice(in, allMice.size(), "Index: ");
		if (mouse == -1) {
			return;
		}
		
		Mouse neededMouse = allMice.get(mouse);
		System.out.printf("Weight: %f\n", neededMouse.getWeight());
		System.out.printf("Is fragile: %b\n", neededMouse.isFragile());
		System.out.printf("Manufacturer: %s\n", neededMouse.getManufacturer());
		System.out.printf("Buttons count: %d\n", neededMouse.getButtonsCount());
		System.out.printf("Is wireless: %b\n", neededMouse.isWireless());
		System.out.printf("Manager:\n\t%s\n", neededMouse.getManager());
		System.out.printf("Room:\n\t%s\n", neededMouse.getRoom());

	}

	@Override
	@Transactional
	public void addOne() {

		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);
		
		Mouse mouse;
		try {
			System.out.print("Weight : ");
			double weight = Double.parseDouble(in.nextLine());
			System.out.print("Is fragile : ");
			String temp1 = in.nextLine();
			boolean fragile = temp1.equals("true") || temp1.equals("t") || temp1.equals("yes") || temp1.equals("y");
			
			List<Manager> allManagers = new ArrayList<Manager>();
			managerRepository.findAll().forEach(elem -> {
				allManagers.add(elem);
				System.out.printf("%d) %s\n", allManagers.size(), elem);
			});
			
			int manager = JRMSupport.readMenuChoice(in, allManagers.size(), "Manager: ");
			if (manager == -1) {
				return;
			}
			
			List<Room> allRooms = new ArrayList<Room>();
			roomRepository.findAll().forEach(elem -> {
				allRooms.add(elem);
				System.out.printf("%d) %s\n", allRooms.size(), elem);
			});
	
			int room = JRMSupport.readMenuChoice(in, allRooms.size(), "Room: ");
			if (room == -1) {
				return;
			}
			
			System.out.print("Manufacturer : ");
			String manufacturer = in.nextLine();
			System.out.print("Buttons count : ");
			int buttonsCount = Integer.parseInt(in.nextLine());
			System.out.print("Is wireless : ");
			String temp2 = in.nextLine();
			boolean wireless = temp2.equals("true") || temp2.equals("t") || temp2.equals("yes") || temp2.equals("y");
			
			mouse = new Mouse();
			mouse.setWeight(weight);
			mouse.setFragile(fragile);
			mouse.setManager(allManagers.get(manager));
			mouse.setRoom(allRooms.get(room));
			mouse.setManufacturer(manufacturer);
			mouse.setButtonsCount(buttonsCount);
			mouse.setWireless(wireless);
		} catch (Throwable t) {
			System.out.println("Incorrect input");
			return;
		}
		
		entityManager.persist(mouse);

	}

	@Override
	public void deleteOne() {

		List<Mouse> allMice = new ArrayList<Mouse>();
		mouseRepository.findAll().forEach(elem -> {
			allMice.add(elem);
			System.out.printf("%d) %s\n", allMice.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);

		int mouse = JRMSupport.readMenuChoice(in, allMice.size(), "Index: ");
		if (mouse == -1) {
			return;
		}

		mouseRepository.delete(allMice.get(mouse));

	}

	@Override
	@Transactional
	public void updateOne() {

		List<Mouse> allMice = new ArrayList<Mouse>();
		mouseRepository.findAll().forEach(elem -> {
			allMice.add(elem);
			System.out.printf("%d) %s\n", allMice.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);

		int monitor = JRMSupport.readMenuChoice(in, allMice.size(), "Index: ");
		if (monitor == -1) {
			return;
		}
		
		Mouse neededMouse = allMice.get(monitor);
		
		System.out.print("Choose option:\n");
		System.out.print("1) Change weight\n");
		System.out.print("2) Change fragile\n");
		System.out.print("3) Change manager\n");
		System.out.print("4) Change room\n");
		System.out.print("5) Change manufacturer\n");
		System.out.print("6) Change buttons count\n");
		System.out.print("7) Change wireless\n");
		System.out.print("8) Go back\n");
		
		boolean exitFlag = false;
		while (!exitFlag) {
			try {
				int choice = Integer.parseInt(in.nextLine());
				switch(choice) {
				case 1:
					System.out.print("New weight: ");
					neededMouse.setWeight(Double.parseDouble(in.nextLine()));
					exitFlag = true;
					break;
				case 2:
					System.out.print("Is fragile: ");
					String temp1 = in.nextLine();
					neededMouse.setFragile(temp1.equals("true") || temp1.equals("t") || temp1.equals("yes") || temp1.equals("y"));
					exitFlag = true;
					break;
				case 3:
					List<Manager> allManagers = new ArrayList<Manager>();
					managerRepository.findAll().forEach(elem -> {
						allManagers.add(elem);
						System.out.printf("%d) %s\n", allManagers.size(), elem);
					});
					
					int manager = JRMSupport.readMenuChoice(in, allManagers.size(), "New manager index: ");
					if (manager == -1) {
						return;
					}
					
					neededMouse.setManager(allManagers.get(manager));
					exitFlag = true;
					break;
				case 4:
					List<Room> allRooms = new ArrayList<Room>();
					roomRepository.findAll().forEach(elem -> {
						allRooms.add(elem);
						System.out.printf("%d) %s\n", allRooms.size(), elem);
					});
					
					int room = JRMSupport.readMenuChoice(in, allRooms.size(), "New room index: ");
					if (room == -1) {
						return;
					}
					
					neededMouse.setRoom(allRooms.get(room));
					exitFlag = true;
					break;
				case 5:
					System.out.print("New manufacturer: ");
					neededMouse.setManufacturer(in.nextLine());
					exitFlag = true;
					break;
				case 6:
					System.out.print("New buttons count: ");
					neededMouse.setButtonsCount(Integer.parseInt(in.nextLine()));
					exitFlag = true;
					break;
				case 7:
					System.out.print("Is wireless: ");
					neededMouse.setWireless(Boolean.parseBoolean(in.nextLine()));
					exitFlag = true;
					break;
				case 8:
					return;
				default:
					break;
				}
			} catch (Throwable t) {
				System.out.println("Incorrect input");
				return;
			}
		}
		
		entityManager.merge(neededMouse);

	}

}
