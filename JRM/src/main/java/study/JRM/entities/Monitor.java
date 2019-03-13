package study.JRM.entities;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Table;

@Entity
@Table(name = "monitors")
public class Monitor extends Equipment {

	@Column(nullable = false, length = 16)
	protected String resolution;
	
	@Column(name="matrix_type", nullable = true, length = 16)
	protected String matrixType;

	public String getResolution() {
		return resolution;
	}

	public void setResolution(String resolution) {
		this.resolution = resolution;
	}

	public String getMatrixType() {
		return matrixType;
	}

	public void setMatrixType(String matrixType) {
		this.matrixType = matrixType;
	}
	
	@Override
	public String toString() {
		return String.format("[Weight: %f, Fragile: %b, Manager: %s, Room: %s, Manufacturer: %s, Resolution: %s, Matrix type: %s]", 
				weight, fragile, manager.getLastName()+ ' ' + manager.getFirstName(), room.getName(), manufacturer, resolution, matrixType);
	}
}
