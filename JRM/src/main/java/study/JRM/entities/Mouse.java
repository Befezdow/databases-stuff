package study.JRM.entities;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Table;

@Entity
@Table(name = "mice")
public class Mouse extends Equipment {

	@Column(name = "buttons_count", nullable = true)
	protected int buttonsCount;
	
	@Column(nullable = true)
	protected boolean wireless;

	public int getButtonsCount() {
		return buttonsCount;
	}

	public void setButtonsCount(int buttonsCount) {
		this.buttonsCount = buttonsCount;
	}

	public boolean isWireless() {
		return wireless;
	}

	public void setWireless(boolean wireless) {
		this.wireless = wireless;
	}
	
	@Override
	public String toString() {
		return String.format("[Weight: %f, Fragile: %b, Manager: %s, Room: %s, Manufacturer: %s, Buttons count: %d, Wireless: %b]", 
				weight, fragile, manager.getLastName()+ ' ' + manager.getFirstName(), room.getName(), manufacturer, buttonsCount, wireless);
	}
}
