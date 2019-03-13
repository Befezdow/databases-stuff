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
@Table(name = "rooms")
public final class Room {

	@Id
	@GeneratedValue(strategy=GenerationType.IDENTITY)
	@Column(insertable = false, updatable = false)
	protected int id;
	
	@Column(unique=true, nullable = false, length = 8)
	private String name;
	
	@Column(nullable = true, length = 256)
	private String description;
	
	@OneToMany(mappedBy="room", targetEntity=Chair.class, fetch=FetchType.LAZY)
	List<Chair> chairs = new ArrayList<Chair>();
	
	@OneToMany(mappedBy="room", targetEntity=DBTable.class, fetch=FetchType.LAZY)
	List<DBTable> tables = new ArrayList<DBTable>();
	
	@OneToMany(mappedBy="room", targetEntity=Monitor.class, fetch=FetchType.LAZY)
	List<Monitor> monitors = new ArrayList<Monitor>();
	
	@OneToMany(mappedBy="room", targetEntity=Mouse.class, fetch=FetchType.LAZY)
	List<Mouse> mice = new ArrayList<Mouse>();

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
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
		return String.format("[Name: %s, Description: %s]", name, description);
	}
}
