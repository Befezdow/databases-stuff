package study.JRM.entities;

import javax.persistence.Column;
import javax.persistence.MappedSuperclass;
import javax.persistence.Table;

@MappedSuperclass
public class Furniture extends DBObject {

	@Column(nullable = true, length = 64)
	protected String material;
	
	@Column(nullable = false)
	protected boolean collapsible;

	public String getMaterial() {
		return material;
	}

	public void setMaterial(String material) {
		this.material = material;
	}

	public boolean isCollapsible() {
		return collapsible;
	}

	public void setCollapsible(boolean collapsible) {
		this.collapsible = collapsible;
	}
}
