export const useNano = () => {
    const nano = useState<Array<Number>>(
        'ejex',
        () => []
    )

    const setNano = (newValue: any) => {
        nano.value = [...nano.value, newValue]
    }

    return {
        nano,
        setNano
    }
}