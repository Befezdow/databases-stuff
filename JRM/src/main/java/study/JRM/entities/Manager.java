package study.JRM.entities;

import java.util.ArrayList;
import java.util.List;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.OneToMany;
import javax.persistence.Table;

@Entity
@Table(name = "managers")
public final class Manager {
	
	@Id
	@GeneratedValue(strategy=GenerationType.IDENTITY)
	@Column(insertable = false, updatable = false)
	private int id;
	
	@Column(name="firstname", nullable = false, length = 32)
	private String firstName;
	
	@Column(name="lastname", nullable = false, length = 32)
	private String lastName;
	
	@Column(nullable = false, length = 32)
	private String patronymic;
	
	@Column(nullable = true, length = 256)
	private String description;
	
	@Column(name="phone_number", nullable = true, length = 32)
	private String phoneNumber;
	
	@OneToMany(mappedBy="manager", targetEntity=Chair.class, fetch=FetchType.LAZY)
	List<Chair> chairs = new ArrayList<Chair>();
	
	@OneToMany(mappedBy="manager", targetEntity=DBTable.class, fetch=FetchType.LAZY)
	List<DBTable> tables = new ArrayList<DBTable>();
	
	@OneToMany(mappedBy="manager", targetEntity=Monitor.class, fetch=FetchType.LAZY)
	List<Monitor> monitors = new ArrayList<Monitor>();
	
	@OneToMany(mappedBy="manager", targetEntity=Mouse.class, fetch=FetchType.LAZY)
	List<Mouse> mice = new ArrayList<Mouse>();

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstname) {
		this.firstName = firstname;
	}

	public String getLastName() {
		return lastName;
	}

	public void setLastName(String lastname) {
		this.lastName = lastname;
	}

	public String getPatronymic() {
		return patronymic;
	}

	public void setPatronymic(String patronymic) {
		this.patronymic = patronymic;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public String getPhoneNumber() {
		return phoneNumber;
	}

	public void setPhoneNumber(String phoneNumber) {
		this.phoneNumber = phoneNumber;
	}

	public List<Chair> getChairs() {
		return chairs;
	}

	public void setChairs(List<Chair> chairs) {
		this.chairs = chairs;
	}

	public List<DBTable> getTables() {
		return tables;
	}

	public void setTables(List<DBTable> tables) {
		this.tables = tables;
	}

	public List<Monitor> getMonitors() {
		return monitors;
	}

	public void setMonitors(List<Monitor> monitors) {
		this.monitors = monitors;
	}

	public List<Mouse> getMice() {
		return mice;
	}

	public void setMice(List<Mouse> mice) {
		this.mice = mice;
	}
	
	@Override
	public String toString() {
		return String.format("[Firstname: %s, Lastname: %s, Patronymic: %s, Phone number: %s, Description: %s]", 
				firstName, lastName, patronymic, phoneNumber, description);
	}
}
