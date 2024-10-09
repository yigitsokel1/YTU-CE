import java.util.*;

public class ProcessManager implements IProcessManager{
    private int used_memory_size;
    private int max_memory_size;
    private HashMap<String, Process> processMaps;
    private LinkedList<Process> waitingProcessList;


    ProcessManager(int max_memory_size){
        this.max_memory_size = max_memory_size;
        this.processMaps = new HashMap<>();
        this.waitingProcessList = new LinkedList<>();
    }

    public int getUsed_memory_size() {
        return used_memory_size;
    }

    public boolean add_process(User u, String processName, int required_memory) {
        if (processMaps.containsKey(processName)) {
            return false;
        }
        // Check if process name already exists in the waiting list
        for (Process p : waitingProcessList) {
            if (p.getName().equals(processName)) {
                return false;
            }
        }

        Process newProcess = new Process(processName, required_memory, u);
        if((used_memory_size + required_memory) <= max_memory_size) {
            used_memory_size += required_memory;
            processMaps.put(processName, newProcess);
            return true;
        }
        else {
            waitingProcessList.add(newProcess);
        }
        return false;
    }

    public boolean remove_process(String name) throws Exception {
        Process removedProcess = processMaps.remove(name);
        if (removedProcess == null) {
            throw new Exception("Process cannot be found!");
        }
        used_memory_size -= removedProcess.getRequired_memory();
        System.out.println(("Used Size : " + used_memory_size));

        Iterator<Process> iterator = waitingProcessList.iterator();
        while (iterator.hasNext()) {
            Process waitingProcess = iterator.next();
            if (waitingProcess.getRequired_memory() + used_memory_size <= max_memory_size) {
                iterator.remove(); // Güvenli bir şekilde listeyi güncelliyoruz
                add_process(waitingProcess.getUser(), waitingProcess.getName(), waitingProcess.getRequired_memory());
            }
        }
        return true;
    }

    public void print_processes() {
        if (processMaps.isEmpty()) {
            System.out.println("There is no processes yet.");
        }

        for (String name: processMaps.keySet()) {
            String value = processMaps.get(name).toString();
            System.out.println(name + " = " + value);
        }
    }

    public void print_waiting_processes() {
        if (waitingProcessList.isEmpty()) {
            System.out.println("Waiting processes list is empty!");
        }
        else{
            for (Process process : waitingProcessList)
                System.out.println(process);

        }
    }
}
