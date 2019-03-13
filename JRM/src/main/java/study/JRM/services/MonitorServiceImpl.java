package study.JRM.services;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.transaction.Transactional;

import org.springframework.beans.factory.annotation.Autowired;

import study.JRM.entities.Manager;
import study.JRM.entities.Monitor;
import study.JRM.entities.Room;
import study.JRM.repositories.ManagerRepository;
import study.JRM.repositories.MonitorRepository;
import study.JRM.repositories.RoomRepository;
import study.JRM.support.JRMSupport;

public class MonitorServiceImpl implements MonitorService {
	
	@Autowired
	private MonitorRepository monitorRepository;
	
	@Autowired
	private ManagerRepository managerRepository;
	
	@Autowired
	private RoomRepository roomRepository;
	
	@PersistenceContext
	private EntityManager entityManager;

	@Override
	public void showAll() {

		monitorRepository.findAll().forEach(elem -> {
			System.out.println(elem);
		});
		
	}

	@Override
	public void showOne() {

		List<Monitor> allMonitors = new ArrayList<Monitor>();
		monitorRepository.findAll().forEach(elem -> {
			allMonitors.add(elem);
			System.out.printf("%d) %s\n", allMonitors.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);
		
		int monitor = JRMSupport.readMenuChoice(in, allMonitors.size(), "Index: ");
		if (monitor == -1) {
			return;
		}
		
		Monitor neededMonitor = allMonitors.get(monitor);
		System.out.printf("Weight: %f\n", neededMonitor.getWeight());
		System.out.printf("Is fragile: %b\n", neededMonitor.isFragile());
		System.out.printf("Manufacturer: %s\n", neededMonitor.getManufacturer());
		System.out.printf("Resolution: %s\n", neededMonitor.getResolution());
		System.out.printf("Matrix type: %f\n", neededMonitor.getMatrixType());
		System.out.printf("Manager:\n\t%s\n", neededMonitor.getManager());
		System.out.printf("Room:\n\t%s\n", neededMonitor.getRoom());
	}

	@Override
	@Transactional
	public void addOne() {

		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);
		
		Monitor monitor;
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
			System.out.print("Resolution : ");
			String resolution = in.nextLine();
			System.out.print("Matrix type : ");
			String matrixType = in.nextLine();
			
			monitor = new Monitor();
			monitor.setWeight(weight);
			monitor.setFragile(fragile);
			monitor.setManager(allManagers.get(manager));
			monitor.setRoom(allRooms.get(room));
			monitor.setManufacturer(manufacturer);
			monitor.setResolution(resolution);
			monitor.setMatrixType(matrixType);
		} catch (Throwable t) {
			System.out.println("Incorrect input");
			return;
		}
		
		entityManager.persist(monitor);

	}

	@Override
	public void deleteOne() {

		List<Monitor> allMonitors = new ArrayList<Monitor>();
		monitorRepository.findAll().forEach(elem -> {
			allMonitors.add(elem);
			System.out.printf("%d) %s\n", allMonitors.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);

		int monitor = JRMSupport.readMenuChoice(in, allMonitors.size(), "Index: ");
		if (monitor == -1) {
			return;
		}

		monitorRepository.delete(allMonitors.get(monitor));

	}

	@Override
	@Transactional
	public void updateOne() {

		List<Monitor> allMonitors = new ArrayList<Monitor>();
		monitorRepository.findAll().forEach(elem -> {
			allMonitors.add(elem);
			System.out.printf("%d) %s\n", allMonitors.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);

		int monitor = JRMSupport.readMenuChoice(in, allMonitors.size(), "Index: ");
		if (monitor == -1) {
			return;
		}
		
		Monitor neededMonitor = allMonitors.get(monitor);
		
		System.out.print("Choose option:\n");
		System.out.print("1) Change weight\n");
		System.out.print("2) Change fragile\n");
		System.out.print("3) Change manager\n");
		System.out.print("4) Change room\n");
		System.out.print("5) Change manufacturer\n");
		System.out.print("6) Change resolution\n");
		System.out.print("7) Change matrix type\n");
		System.out.print("8) Go back\n");
		
		boolean exitFlag = false;
		while (!exitFlag) {
			try {
				int choice = Integer.parseInt(in.nextLine());
				switch(choice) {
				case 1:
					System.out.print("New weight: ");
					neededMonitor.setWeight(Double.parseDouble(in.nextLine()));
					exitFlag = true;
					break;
				case 2:
					System.out.print("Is fragile: ");
					String temp1 = in.nextLine();
					neededMonitor.setFragile(temp1.equals("true") || temp1.equals("t") || temp1.equals("yes") || temp1.equals("y"));
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
					
					neededMonitor.setManager(allManagers.get(manager));
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
					
					neededMonitor.setRoom(allRooms.get(room));
					exitFlag = true;
					break;
				case 5:
					System.out.print("New manufacturer: ");
					neededMonitor.setManufacturer(in.nextLine());
					exitFlag = true;
					break;
				case 6:
					System.out.print("New resolution: ");
					neededMonitor.setResolution(in.nextLine());
					exitFlag = true;
					break;
				case 7:
					System.out.print("New matrix type: ");
					neededMonitor.setMatrixType(in.nextLine());
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
		
		entityManager.merge(neededMonitor);
	}

}
