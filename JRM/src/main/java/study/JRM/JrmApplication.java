package study.JRM;

import java.util.Scanner;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import study.JRM.services.ChairService;
import study.JRM.services.ChairServiceImpl;
import study.JRM.services.DBTableService;
import study.JRM.services.DBTableServiceImpl;
import study.JRM.services.ManagerService;
import study.JRM.services.ManagerServiceImpl;
import study.JRM.services.MonitorService;
import study.JRM.services.MonitorServiceImpl;
import study.JRM.services.MouseService;
import study.JRM.services.MouseServiceImpl;
import study.JRM.services.RoomService;
import study.JRM.services.RoomServiceImpl;

@SpringBootApplication
public class JrmApplication {
	
	private static final Logger LOGGER = LoggerFactory.getLogger(JrmApplication.class);
	
	@Bean 
	ManagerService ManagerService() {
		return new ManagerServiceImpl();
	}
	
	@Bean 
	RoomService RoomService() {
		return new RoomServiceImpl();
	}
	
	@Bean
	ChairService ChairService() {
		return new ChairServiceImpl();
	}
	
	@Bean
	DBTableService DBTableService() {
		return new DBTableServiceImpl();
	}
	
	@Bean
	MonitorService MonitorService() {
		return new MonitorServiceImpl();
	}
	
	@Bean
	MouseService MouseService() {
		return new MouseServiceImpl();
	}

	public static void main(String[] args) {
		SpringApplication.run(JrmApplication.class, args);
	}
	
	@Bean
	public CommandLineRunner run(final ManagerService managerService, final RoomService roomService,
			final ChairService chairService, final DBTableService tableService, final MonitorService monitorService,
			final MouseService mouseService) {
		return new CommandLineRunner() {
			
			@Override
			public void run(String... arg0) throws Exception {
				
				while(true) {
					System.out.println("--- Main menu ---");
					System.out.println("1) Show menu");
					System.out.println("2) Show detail menu");
					System.out.println("3) Add menu");
					System.out.println("4) Update menu");
					System.out.println("5) Delete menu");
					System.out.println("6) Exit");
					
					@SuppressWarnings("resource")
					Scanner in = new Scanner(System.in);
					
					int choice;
					try {
						choice = Integer.parseInt(in.nextLine());
					} catch (Throwable t) {
						System.out.println("Incorrect input");
						continue;
					}
					
					switch (choice) {
					case 1: {
						boolean exitFlag = false;
						while(!exitFlag) {
							System.out.println("--- Show menu ---");
							System.out.println("1) Show managers");
							System.out.println("2) Show rooms");
							System.out.println("3) Show chairs");
							System.out.println("4) Show tables");
							System.out.println("5) Show monitors");
							System.out.println("6) Show mice");
							System.out.println("7) Go back");
							
							int choice1;
							try {
								choice1 = Integer.parseInt(in.nextLine());
							} catch (Throwable t) {
								System.out.println("Incorrect input");
								continue;
							}
							
							switch (choice1) {
							case 1:
								managerService.showAll();
								break;
							case 2:
								roomService.showAll();
								break;
							case 3:
								chairService.showAll();
								break;
							case 4:
								tableService.showAll();
								break;
							case 5:
								monitorService.showAll();
								break;
							case 6:
								mouseService.showAll();
								break;
							case 7:
								exitFlag = true;
								break;
							default:
								break;
							}
						}
						break;
					}
					case 2: {
						boolean exitFlag = false;
						while(!exitFlag) {
							System.out.println("--- Show detail menu ---");
							System.out.println("1) Show detail manager");
							System.out.println("2) Show detail room");
							System.out.println("3) Show detail chair");
							System.out.println("4) Show detail table");
							System.out.println("5) Show detail monitor");
							System.out.println("6) Show detail mouse");
							System.out.println("7) Go back");
							
							int choice1;
							try {
								choice1 = Integer.parseInt(in.nextLine());
							} catch (Throwable t) {
								System.out.println("Incorrect input");
								continue;
							}
							
							switch (choice1) {
							case 1:
								managerService.showOne();
								break;
							case 2:
								roomService.showOne();
								break;
							case 3:
								chairService.showOne();
								break;
							case 4:
								tableService.showOne();
								break;
							case 5:
								monitorService.showOne();
								break;
							case 6:
								mouseService.showOne();
								break;
							case 7:
								exitFlag = true;
								break;
							default:
								break;
							}
						}
						break;
					}
					case 3: {
						boolean exitFlag = false;
						while(!exitFlag) {
							System.out.println("--- Add menu ---");
							System.out.println("1) Add manager");
							System.out.println("2) Add room");
							System.out.println("3) Add chair");
							System.out.println("4) Add table");
							System.out.println("5) Add monitor");
							System.out.println("6) Add mouse");
							System.out.println("7) Go back");
							
							int choice1;
							try {
								choice1 = Integer.parseInt(in.nextLine());
							} catch (Throwable t) {
								System.out.println("Incorrect input");
								continue;
							}
							
							switch (choice1) {
							case 1:
								managerService.addOne();
								break;
							case 2:
								roomService.addOne();
								break;
							case 3:
								chairService.addOne();
								break;
							case 4:
								tableService.addOne();
								break;
							case 5:
								monitorService.addOne();
								break;
							case 6:
								mouseService.addOne();
								break;
							case 7:
								exitFlag = true;
								break;
							default:
								break;
							}
						}
						break;
					}
					case 4: {
						boolean exitFlag = false;
						while(!exitFlag) {
							System.out.println("--- Update menu ---");
							System.out.println("1) Update manager");
							System.out.println("2) Update room");
							System.out.println("3) Update chair");
							System.out.println("4) Update table");
							System.out.println("5) Update monitor");
							System.out.println("6) Update mouse");
							System.out.println("7) Go back");
							
							int choice1;
							try {
								choice1 = Integer.parseInt(in.nextLine());
							} catch (Throwable t) {
								System.out.println("Incorrect input");
								continue;
							}
							
							switch (choice1) {
							case 1:
								managerService.updateOne();
								break;
							case 2:
								roomService.updateOne();
								break;
							case 3:
								chairService.updateOne();
								break;
							case 4:
								tableService.updateOne();
								break;
							case 5:
								monitorService.updateOne();
								break;
							case 6:
								mouseService.updateOne();
								break;
							case 7:
								exitFlag = true;
								break;
							default:
								break;
							}
						}
						break;
					}
					case 5: {
						boolean exitFlag = false;
						while(!exitFlag) {
							System.out.println("--- Delete menu ---");
							System.out.println("1) Delete manager");
							System.out.println("2) Delete room");
							System.out.println("3) Delete chair");
							System.out.println("4) Delete table");
							System.out.println("5) Delete monitor");
							System.out.println("6) Delete mouse");
							System.out.println("7) Go back");
							
							int choice1;
							try {
								choice1 = Integer.parseInt(in.nextLine());
							} catch (Throwable t) {
								System.out.println("Incorrect input");
								continue;
							}
							
							switch (choice1) {
							case 1:
								managerService.deleteOne();
								break;
							case 2:
								roomService.deleteOne();
								break;
							case 3:
								chairService.deleteOne();
								break;
							case 4:
								tableService.deleteOne();
								break;
							case 5:
								monitorService.deleteOne();
								break;
							case 6:
								mouseService.deleteOne();
								break;
							case 7:
								exitFlag = true;
								break;
							default:
								break;
							}
						}
						break;
					}
					case 6: {
						return;
					}
					default:
						break;
					}
				}
			}
		};
	}
}
