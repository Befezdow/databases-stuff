package study.JRM.entities;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Table;

@Entity
@Table(name = "tables")
public class DBTable extends Furniture {

	@Column(nullable = true)
	protected double height;
	
	@Column(name="table_type", nullable = true,  length = 32)
	protected String tableType;

	public double getHeight() {
		return height;
	}

	public void setHeight(double height) {
		this.height = height;
	}

	public String getTableType() {
		return tableType;
	}

	public void setTableType(String tableType) {
		this.tableType = tableType;
	}
	
	@Override
	public String toString() {
		return String.format("[Weight: %f, Fragile: %b, Manager: %s, Room: %s, Material: %s, Collapsible: %b, Height: %f, Table type: %s]", 
				weight, fragile, manager.getLastName()+ ' ' + manager.getFirstName(), room.getName(), material, collapsible, height, tableType);
	}
}
