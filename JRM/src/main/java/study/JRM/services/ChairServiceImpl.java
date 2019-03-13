package study.JRM.services;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.transaction.Transactional;

import org.springframework.beans.factory.annotation.Autowired;

import study.JRM.entities.Chair;
import study.JRM.entities.Manager;
import study.JRM.entities.Room;
import study.JRM.repositories.ChairRepository;
import study.JRM.repositories.ManagerRepository;
import study.JRM.repositories.RoomRepository;
import study.JRM.support.JRMSupport;

public class ChairServiceImpl implements ChairService {
	
	@Autowired
	private ChairRepository chairRepository;
	
	@Autowired
	private ManagerRepository managerRepository;
	
	@Autowired
	private RoomRepository roomRepository;
	
	@PersistenceContext
	private EntityManager entityManager;
	
	@Override
	public void showAll() {
		
		chairRepository.findAll().forEach(elem -> {
			System.out.println(elem);
		});

	}

	@Override
	public void showOne() {

		List<Chair> allChairs = new ArrayList<Chair>();
		chairRepository.findAll().forEach(elem -> {
			allChairs.add(elem);
			System.out.printf("%d) %s\n", allChairs.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);
		
		int chair = JRMSupport.readMenuChoice(in, allChairs.size(), "Index: ");
		if (chair == -1) {
			return;
		}
		
		Chair neededChair = allChairs.get(chair);
		System.out.printf("Weight: %f\n", neededChair.getWeight());
		System.out.printf("Is fragile: %b\n", neededChair.isFragile());
		System.out.printf("Material: %s\n", neededChair.getMaterial());
		System.out.printf("Is Collapsible: %b\n", neededChair.isCollapsible());
		System.out.printf("Chair type: %s\n", neededChair.getChairType());
		System.out.printf("Max weight: %f\n", neededChair.getMaxWeight());
		System.out.printf("Manager:\n\t%s\n", neededChair.getManager());
		System.out.printf("Room:\n\t%s\n", neededChair.getRoom());
	}

	@Override
	@Transactional
	public void addOne() {

		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);
		
		Chair chair;
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
			
			System.out.print("Material : ");
			String material = in.nextLine();
			System.out.print("Is collapsible : ");
			String temp2 = in.nextLine();
			boolean collapsible = temp2.equals("true") || temp2.equals("t") || temp2.equals("yes") || temp2.equals("y");
			System.out.print("Chair type : ");
			String chairType = in.nextLine();
			System.out.print("Max weight : ");
			double maxWeight = Double.parseDouble(in.nextLine());
			
			chair = new Chair();
			chair.setWeight(weight);
			chair.setFragile(fragile);
			chair.setManager(allManagers.get(manager));
			chair.setRoom(allRooms.get(room));
			chair.setMaterial(material);
			chair.setCollapsible(collapsible);
			chair.setChairType(chairType);
			chair.setMaxWeight(maxWeight);
		} catch (Throwable t) {
			System.out.println("Incorrect input");
			return;
		}
		
		entityManager.persist(chair);
	}

	@Override
	public void deleteOne() {

		List<Chair> allChairs = new ArrayList<Chair>();
		chairRepository.findAll().forEach(elem -> {
			allChairs.add(elem);
			System.out.printf("%d) %s\n", allChairs.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);

		int chair = JRMSupport.readMenuChoice(in, allChairs.size(), "Index: ");
		if (chair == -1) {
			return;
		}

		chairRepository.delete(allChairs.get(chair));

	}

	@Override
	@Transactional
	public void updateOne() {

		List<Chair> allChairs = new ArrayList<Chair>();
		chairRepository.findAll().forEach(elem -> {
			allChairs.add(elem);
			System.out.printf("%d) %s\n", allChairs.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);

		int chair = JRMSupport.readMenuChoice(in, allChairs.size(), "Index: ");
		if (chair == -1) {
			return;
		}
		
		Chair neededChair = allChairs.get(chair);
		
		System.out.print("Choose option:\n");
		System.out.print("1) Change weight\n");
		System.out.print("2) Change fragile\n");
		System.out.print("3) Change manager\n");
		System.out.print("4) Change room\n");
		System.out.print("5) Change material\n");
		System.out.print("6) Change collapsible\n");
		System.out.print("7) Change chair type\n");
		System.out.print("8) Change max weight\n");
		System.out.print("9) Go back\n");
		
		boolean exitFlag = false;
		while (!exitFlag) {
			try {
				int choice = Integer.parseInt(in.nextLine());
				switch(choice) {
				case 1:
					System.out.print("New weight: ");
					neededChair.setWeight(Double.parseDouble(in.nextLine()));
					exitFlag = true;
					break;
				case 2:
					System.out.print("Is fragile: ");
					String temp1 = in.nextLine();
					neededChair.setFragile(temp1.equals("true") || temp1.equals("t") || temp1.equals("yes") || temp1.equals("y"));
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
					
					neededChair.setManager(allManagers.get(manager));
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
					
					neededChair.setRoom(allRooms.get(room));
					exitFlag = true;
					break;
				case 5:
					System.out.print("New material: ");
					neededChair.setMaterial(in.nextLine());
					exitFlag = true;
					break;
				case 6:
					System.out.print("Is collapsible: ");
					String temp2 = in.nextLine();
					neededChair.setCollapsible(temp2.equals("true") || temp2.equals("t") || temp2.equals("yes") || temp2.equals("y"));
					exitFlag = true;
					break;
				case 7:
					System.out.print("New chair type: ");
					neededChair.setChairType(in.nextLine());
					exitFlag = true;
					break;
				case 8:
					System.out.print("New max weight: ");
					neededChair.setMaxWeight(Double.parseDouble(in.nextLine()));
					exitFlag = true;
					break;
				case 9:
					return;
				default:
					break;
				}
			} catch (Throwable t) {
				System.out.println("Incorrect input");
				return;
			}
		}
		
		entityManager.merge(neededChair);
	}

}
