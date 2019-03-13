package study.JRM.services;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.transaction.Transactional;

import org.springframework.beans.factory.annotation.Autowired;

import study.JRM.entities.DBTable;
import study.JRM.entities.Manager;
import study.JRM.entities.Room;
import study.JRM.repositories.DBTableRepository;
import study.JRM.repositories.ManagerRepository;
import study.JRM.repositories.RoomRepository;
import study.JRM.support.JRMSupport;

public class DBTableServiceImpl implements DBTableService {
	
	@Autowired
	private DBTableRepository tableRepository;
	
	@Autowired
	private ManagerRepository managerRepository;
	
	@Autowired
	private RoomRepository roomRepository;
	
	@PersistenceContext
	private EntityManager entityManager;
	
	@Override
	public void showAll() {

		tableRepository.findAll().forEach(elem -> {
			System.out.println(elem);
		});

	}

	@Override
	public void showOne() {

		List<DBTable> allTables = new ArrayList<DBTable>();
		tableRepository.findAll().forEach(elem -> {
			allTables.add(elem);
			System.out.printf("%d) %s\n", allTables.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);
		
		int table = JRMSupport.readMenuChoice(in, allTables.size(), "Index: ");
		if (table == -1) {
			return;
		}
		
		DBTable neededTable = allTables.get(table);
		System.out.printf("Weight: %f\n", neededTable.getWeight());
		System.out.printf("Is fragile: %b\n", neededTable.isFragile());
		System.out.printf("Material: %s\n", neededTable.getMaterial());
		System.out.printf("Is Collapsible: %b\n", neededTable.isCollapsible());
		System.out.printf("Table type: %s\n", neededTable.getTableType());
		System.out.printf("Height: %f\n", neededTable.getHeight());
		System.out.printf("Manager:\n\t%s\n", neededTable.getManager());
		System.out.printf("Room:\n\t%s\n", neededTable.getRoom());

	}

	@Override
	@Transactional
	public void addOne() {

		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);
		
		DBTable table;
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
			
			System.out.print("Material: ");
			String material = in.nextLine();
			System.out.print("Is collapsible: ");
			String temp2 = in.nextLine();
			boolean collapsible = temp2.equals("true") || temp2.equals("t") || temp2.equals("yes") || temp2.equals("y");
			System.out.print("Table type: ");
			String tableType = in.nextLine();
			System.out.print("Height: ");
			double height = Double.parseDouble(in.nextLine());
			
			table = new DBTable();
			table.setWeight(weight);
			table.setFragile(fragile);
			table.setManager(allManagers.get(manager));
			table.setRoom(allRooms.get(room));
			table.setMaterial(material);
			table.setCollapsible(collapsible);
			table.setTableType(tableType);
			table.setHeight(height);
		} catch (Throwable t) {
			System.out.println("Incorrect input");
			return;
		}
		
		entityManager.persist(table);

	}

	@Override
	public void deleteOne() {

		List<DBTable> allTables = new ArrayList<DBTable>();
		tableRepository.findAll().forEach(elem -> {
			allTables.add(elem);
			System.out.printf("%d) %s\n", allTables.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);

		int table = JRMSupport.readMenuChoice(in, allTables.size(), "Index: ");
		if (table == -1) {
			return;
		}

		tableRepository.delete(allTables.get(table));

	}

	@Override
	@Transactional
	public void updateOne() {

		List<DBTable> allTables = new ArrayList<DBTable>();
		tableRepository.findAll().forEach(elem -> {
			allTables.add(elem);
			System.out.printf("%d) %s\n", allTables.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);

		int table = JRMSupport.readMenuChoice(in, allTables.size(), "Index: ");
		if (table == -1) {
			return;
		}
		
		DBTable neededTable = allTables.get(table);
		
		System.out.print("Choose option:\n");
		System.out.print("1) Change weight\n");
		System.out.print("2) Change fragile\n");
		System.out.print("3) Change manager\n");
		System.out.print("4) Change room\n");
		System.out.print("5) Change material\n");
		System.out.print("6) Change collapsible\n");
		System.out.print("7) Change table type\n");
		System.out.print("8) Change height\n");
		System.out.print("9) Go back\n");
		
		boolean exitFlag = false;
		while (!exitFlag) {
			try {
				int choice = Integer.parseInt(in.nextLine());
				switch(choice) {
				case 1:
					System.out.print("New weight: ");
					neededTable.setWeight(Double.parseDouble(in.nextLine()));
					exitFlag = true;
					break;
				case 2:
					System.out.print("Is fragile: ");
					String temp1 = in.nextLine();
					neededTable.setFragile(temp1.equals("true") || temp1.equals("t") || temp1.equals("yes") || temp1.equals("y"));
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
					
					neededTable.setManager(allManagers.get(manager));
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
					
					neededTable.setRoom(allRooms.get(room));
					exitFlag = true;
					break;
				case 5:
					System.out.print("New material: ");
					neededTable.setMaterial(in.nextLine());
					exitFlag = true;
					break;
				case 6:
					System.out.print("Is collapsible: ");
					String temp2 = in.nextLine();
					neededTable.setCollapsible(temp2.equals("true") || temp2.equals("t") || temp2.equals("yes") || temp2.equals("y"));
					exitFlag = true;
					break;
				case 7:
					System.out.print("New table type: ");
					neededTable.setTableType(in.nextLine());
					exitFlag = true;
					break;
				case 8:
					System.out.print("New height: ");
					neededTable.setHeight(Double.parseDouble(in.nextLine()));
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
		
		entityManager.merge(neededTable);

	}

}
