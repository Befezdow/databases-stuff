package study.JRM.services;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.transaction.Transactional;

import org.springframework.beans.factory.annotation.Autowired;

import study.JRM.entities.Manager;
import study.JRM.repositories.ManagerRepository;
import study.JRM.support.JRMSupport;

public class ManagerServiceImpl implements ManagerService {
	
	@Autowired
	private ManagerRepository repository;
	
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

		List<Manager> allManagers = new ArrayList<Manager>();
		repository.findAll().forEach(elem -> {
			allManagers.add(elem);
			System.out.printf("%d) %s\n", allManagers.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);
		
		int manager = JRMSupport.readMenuChoice(in, allManagers.size(), "Index: ");
		if (manager == -1) {
			return;
		}
		
		Manager neededManager = allManagers.get(manager);
		System.out.printf("First name: %s\n", neededManager.getFirstName());
		System.out.printf("Last name: %s\n", neededManager.getLastName());
		System.out.printf("Patronymic: %s\n", neededManager.getPatronymic());
		System.out.printf("Phone number: %s\n", neededManager.getPhoneNumber());
		System.out.printf("Description: %s\n", neededManager.getDescription());
		System.out.printf("Chairs:\n");
		neededManager.getChairs().forEach(elem -> {
			System.out.printf("\tWeight: %f, Is fragile: %b, Material: %s, Is collapsible: %b, Chair type: %s, Max weight:%f, Room: %s\n",
					elem.getWeight(), elem.isFragile(), elem.getMaterial(), elem.isCollapsible(), elem.getChairType(), elem.getMaxWeight(), elem.getRoom().getName());
		});
		System.out.printf("Tables:\n");
		neededManager.getTables().forEach(elem -> {
			System.out.printf("\tWeight: %f, Is fragile: %b, Material: %s, Is collapsible: %b, Table type: %s, Height:%f, Room: %s\n",
					elem.getWeight(), elem.isFragile(), elem.getMaterial(), elem.isCollapsible(), elem.getTableType(), elem.getHeight(), elem.getRoom().getName());
		});
		System.out.printf("Monitors:\n");
		neededManager.getMonitors().forEach(elem -> {
			System.out.printf("\tWeight: %f, Is fragile: %b, Manufacturer: %s, Resolution: %b, Matrix type: %s, Room: %s\n",
					elem.getWeight(), elem.isFragile(), elem.getManufacturer(), elem.getResolution(), elem.getMatrixType(), elem.getRoom().getName());
		});
		System.out.printf("Mice:\n");
		neededManager.getMice().forEach(elem -> {
			System.out.printf("\tWeight: %f, Is fragile: %b, Manufacturer: %s, Buttons count: %b, Is wireless: %s, Room: %s\n",
					elem.getWeight(), elem.isFragile(), elem.getManufacturer(), elem.getButtonsCount(), elem.isWireless(), elem.getRoom().getName());
		});
	}

	@Override
	@Transactional
	public void addOne() {
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);
		
		Manager manager;
		try {
			System.out.print("First name : ");
			String firstName = in.nextLine();
			System.out.print("Last name : ");
			String lastName = in.nextLine();
			System.out.print("Patronymic : ");
			String patronymic = in.nextLine();
			System.out.print("Description : ");
			String description = in.nextLine();
			System.out.print("Phone number : ");
			String phoneNumber = in.nextLine();
			
			manager = new Manager();
			manager.setFirstName(firstName);
			manager.setLastName(lastName);
			manager.setPatronymic(patronymic);
			manager.setDescription(description);
			manager.setPhoneNumber(phoneNumber);
		} catch (Throwable t) {
			System.out.println("Incorrect input");
			return;
		}
		
		entityManager.persist(manager);
		
	}

	@Override
	public void deleteOne() {

		List<Manager> allManagers = new ArrayList<Manager>();
		repository.findAll().forEach(elem -> {
			allManagers.add(elem);
			System.out.printf("%d) %s\n", allManagers.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);

		int manager = JRMSupport.readMenuChoice(in, allManagers.size(), "Index: ");
		if (manager == -1) {
			return;
		}

		repository.delete(allManagers.get(manager));
	}

	@Override
	@Transactional
	public void updateOne() {
		
		List<Manager> allManagers = new ArrayList<Manager>();
		repository.findAll().forEach(elem -> {
			allManagers.add(elem);
			System.out.printf("%d) %s\n", allManagers.size(), elem);
		});
		
		@SuppressWarnings("resource")
		Scanner in = new Scanner(System.in);

		int manager = JRMSupport.readMenuChoice(in, allManagers.size(), "Index: ");
		if (manager == -1) {
			return;
		}
		
		Manager neededManager = allManagers.get(manager);
		
		System.out.print("Choose option:\n");
		System.out.print("1) Change first name\n");
		System.out.print("2) Change last name\n");
		System.out.print("3) Change patronymic\n");
		System.out.print("4) Change phone number\n");
		System.out.print("5) Change description\n");
		System.out.print("6) Go back\n");
		
		boolean exitFlag = false;
		while (!exitFlag) {
			try {
				int choice = Integer.parseInt(in.nextLine());
				switch(choice) {
				case 1:
					System.out.print("New first name: ");
					neededManager.setFirstName(in.nextLine());
					exitFlag = true;
					break;
				case 2:
					System.out.print("New last name: ");
					neededManager.setLastName(in.nextLine());
					exitFlag = true;
					break;
				case 3:
					System.out.print("New patronymic: ");
					neededManager.setPatronymic(in.nextLine());
					exitFlag = true;
					break;
				case 4:
					System.out.print("New phone number: ");
					neededManager.setPhoneNumber(in.nextLine());
					exitFlag = true;
					break;
				case 5:
					System.out.print("New description: ");
					neededManager.setDescription(in.nextLine());
					exitFlag = true;
					break;
				case 6:
					return;
				default:
					break;
				}
			} catch (Throwable t) {
				System.out.println("Incorrect input");
				return;
			}
		}
		
		entityManager.merge(neededManager);
	}
}
