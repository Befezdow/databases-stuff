package study.JRM.entities;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Table;

@Entity
@Table(name = "chairs")
public class Chair extends Furniture {

	@Column(name="chair_type", nullable = true, length = 32)
	protected String chairType;
	
	@Column(name="max_weight", nullable = true)
	protected double maxWeight;

	public String getChairType() {
		return chairType;
	}

	public void setChairType(String chairType) {
		this.chairType = chairType;
	}

	public double getMaxWeight() {
		return maxWeight;
	}

	public void setMaxWeight(double maxWeight) {
		this.maxWeight = maxWeight;
	}
	
	@Override
	public String toString() {
		return String.format("[Weight: %f, Fragile: %b, Manager: %s, Room: %s, Material: %s, Collapsible: %b, Chair type: %s, Max weight: %f]", 
				weight, fragile, manager.getLastName()+ ' ' + manager.getFirstName(), room.getName(), material, collapsible, chairType, maxWeight);
	}
}
