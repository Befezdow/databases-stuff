package study.JRM.entities;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.Table;
import javax.persistence.ManyToOne;
import javax.persistence.MappedSuperclass;

@MappedSuperclass
public abstract class DBObject {
	
	@Id
	@GeneratedValue(strategy=GenerationType.IDENTITY)
	@Column
	protected int id;
	
	@Column(nullable = false)
	protected double weight;
	
	@Column(nullable = true)
	protected boolean fragile;
	
	@ManyToOne(optional = false)
    @JoinColumn(name = "manager", nullable=false)
	protected Manager manager;
	
	@ManyToOne(optional = false)
    @JoinColumn(name = "room", nullable=false)
	protected Room room;

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public double getWeight() {
		return weight;
	}

	public void setWeight(double weight) {
		this.weight = weight;
	}

	public boolean isFragile() {
		return fragile;
	}

	public void setFragile(boolean fragile) {
		this.fragile = fragile;
	}

	public Manager getManager() {
		return manager;
	}

	public void setManager(Manager manager) {
		this.manager = manager;
	}

	public Room getRoom() {
		return room;
	}

	public void setRoom(Room room) {
		this.room = room;
	}
}
